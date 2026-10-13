// ============================================================
//  GRAVADOR DE EEPROM - UNO (ESCRAVO I2C)
//  Recebe pacotes de 4 bytes do Nano: [comando, endereco_H, endereco_L, dado]
//  O endereco fisico da EEPROM e dirigido pelo Nano (D2..D12).
//  O UNO controla dados (D2..D9), CE, OE e WE.
//  Recomendado: resistor de 10k para +5V em CE, OE e WE (evita escrita
//  acidental enquanto o UNO esta reiniciando).
// ============================================================
#include <Wire.h>

#define CE 10
#define OE 11
#define WE 12

#define ENDERECO_I2C 8
#define CMD_GRAVAR   1
#define CMD_LIBERAR  2

// ATENCAO: o bit 0 do dado sai no pino 9 e o bit 7 no pino 2. Confira a ligacao.
const byte pinosUNO[8] = {9, 8, 7, 6, 5, 4, 3, 2};

// compartilhados entre a interrupcao I2C e o loop()
volatile bool     novoPacote = false;
volatile uint8_t  comandoRx  = 0;
volatile uint16_t enderecoRx = 0;
volatile uint8_t  dadoRx     = 0;
volatile uint8_t  status     = 0;   // 0 = ocupado, 1 = ok, 2 = falha na verificacao

void extrair_dado(uint8_t dado) // joga o valor nas portas digitais
{
  for (uint8_t n = 0; n < 8; n++)
    digitalWrite(pinosUNO[n], (dado >> n) & 1);
}

uint8_t lerPinos()
{
  uint8_t v = 0;
  for (uint8_t n = 0; n < 8; n++)
    v |= (uint8_t)digitalRead(pinosUNO[n]) << n;
  return v;
}

void dadosComoSaida()
{
  for (uint8_t n = 0; n < 8; n++)
    pinMode(pinosUNO[n], OUTPUT);
}

void dadosComoEntrada()
{
  for (uint8_t n = 0; n < 8; n++)
    pinMode(pinosUNO[n], INPUT);
}

// retoma o controle de CE/OE/WE (apos liberarTudo() eles ficam em alta impedancia)
void assumirControle()
{
  digitalWrite(CE, HIGH); pinMode(CE, OUTPUT);
  digitalWrite(OE, HIGH); pinMode(OE, OUTPUT);
  digitalWrite(WE, HIGH); pinMode(WE, OUTPUT);
}

void EEPROMM_dados(uint8_t dado)
{
  // a EEPROM NAO pode dirigir o barramento enquanto o UNO escreve nele
  assumirControle();

  dadosComoSaida();
  extrair_dado(dado);

  // ciclo de escrita (pulso de WE com CE baixo)
  digitalWrite(CE, LOW);
  delayMicroseconds(1);
  digitalWrite(WE, LOW);
  delayMicroseconds(1);          // minimo ~100 ns
  digitalWrite(WE, HIGH);        // o dado e travado na subida de WE
  digitalWrite(CE, HIGH);

  dadosComoEntrada();            // solta o barramento
  delay(10);                     // tempo de escrita interno da EEPROM (tWC)
}

bool EEPROMM_leitura(uint8_t &valor)
{
  dadosComoEntrada();
  digitalWrite(WE, HIGH);
  digitalWrite(CE, LOW);
  digitalWrite(OE, LOW);         // ativa saida da EEPROM
  delayMicroseconds(5);

  uint8_t leitura1 = lerPinos();
  delayMicroseconds(5);
  uint8_t leitura2 = lerPinos();

  digitalWrite(OE, HIGH);
  digitalWrite(CE, HIGH);

  valor = leitura1;
  return leitura1 == leitura2;   // duas leituras diferentes = barramento instavel
}

void liberarTudo() // alta impedancia em tudo, para o computador assumir a EEPROM
{
  dadosComoEntrada();
  pinMode(CE, INPUT);
  pinMode(OE, INPUT);
  pinMode(WE, INPUT);
}

// ----- interrupcoes I2C: so copiam dados, nada de delay() ou Serial aqui -----
void receberEventos_Nano(int numBytes)
{
  // chegam quatro bytes: comando, endereco MSB, endereco LSB, dado
  if (numBytes != 4)
  {
    while (Wire.available()) Wire.read();
    return;
  }

  uint8_t cmd = Wire.read();
  uint8_t h   = Wire.read();
  uint8_t l   = Wire.read();
  uint8_t d   = Wire.read();

  if (novoPacote) return;        // ainda ocupado com o anterior

  comandoRx  = cmd;
  enderecoRx = ((uint16_t)h << 8) | l;
  dadoRx     = d;
  status     = 0;
  novoPacote = true;
}

void operacao_finalizada()
{
  Wire.write((uint8_t)status);
  if (status != 0) status = 0;   // o resultado e entregue uma unica vez
}

void setup()
{
  Serial.begin(9600);

  // nivel alto ANTES de virar saida, para nao gerar pulso falso em WE
  digitalWrite(CE, HIGH); pinMode(CE, OUTPUT);
  digitalWrite(OE, HIGH); pinMode(OE, OUTPUT);
  digitalWrite(WE, HIGH); pinMode(WE, OUTPUT);
  dadosComoEntrada();

  Wire.begin(ENDERECO_I2C);
  Wire.onReceive(receberEventos_Nano);
  Wire.onRequest(operacao_finalizada);
}

void loop() // o trabalho pesado fica aqui, fora da interrupcao
{
  if (!novoPacote) return;

  uint8_t  cmd      = comandoRx;
  uint16_t endereco = enderecoRx;
  uint8_t  dado     = dadoRx;

  if (cmd == CMD_GRAVAR)
  {
    EEPROMM_dados(dado);

    uint8_t lido = 0;
    bool estavel = EEPROMM_leitura(lido);
    bool ok = estavel && (lido == dado);

    Serial.print(endereco, HEX);
    Serial.print(": ");
    if (ok) { Serial.print(lido, HEX); Serial.println(" ok"); }
    else    { Serial.print("xx esperado "); Serial.print(dado, HEX);
              Serial.print(" lido "); Serial.println(lido, HEX); }

    novoPacote = false;
    status = ok ? 1 : 2;
  }
  else if (cmd == CMD_LIBERAR)
  {
    liberarTudo();
    Serial.println("Pinos liberados");
    novoPacote = false;
    status = 1;
  }
  else
  {
    novoPacote = false;
    status = 2;
  }
}
