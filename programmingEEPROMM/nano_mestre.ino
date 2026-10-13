// ============================================================
//  PROGRAMADOR DE MICROCODIGO - NANO (MESTRE)
//  Calcula a palavra de controle, coloca o endereco nos pinos D2..D12
//  e manda o dado ao UNO (escravo I2C), que grava e verifica a EEPROM.
//  Ligacoes: GND comum, A4 com A4 (SDA), A5 com A5 (SCL)
//  Uso: abra o Serial (9600), digite 1, 2 ou 3 = qual EEPROM gravar
//       1 = bits 0-7, 2 = bits 8-15, 3 = bits 16-23 da palavra de controle
//       (troque a EEPROM no soquete e rode de novo para cada uma)
// ============================================================
#include <Wire.h>

#define ESCRAVO       8          // endereco I2C do UNO
#define I2C_CLOCK_HZ  100000UL   // 100 kHz
#define TIMEOUT_MS    2000UL

#define CMD_GRAVAR    1
#define CMD_LIBERAR   2

// bit 0 do endereco -> D2, ..., bit 10 -> D12
const byte pinosNANO[11] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

// ---------- ativacao dos modulos ----------
#define HLT     0x00001UL //clock. Aqui e logico (1 = parar); no hardware e ativo em LOW (invertido em palavraFinal)
#define JMP     0x00002UL
#define PO      0x00004UL
#define PE      0x00008UL
#define MI      0x00010UL //mar
#define RO      0x00020UL //ram
#define RI      0x00040UL
#define II      0x00080UL //instruction register
#define IO      0x00100UL
#define AI      0x00200UL //a register
#define AO      0x00400UL
#define BI      0x00800UL //b register
#define OI      0x01000UL //output register
#define OO      0x02000UL //output register
#define ALU_0   0x04000UL //00 add/sub, 01 or, 10 and, 11 xor
#define ALU_1   0x08000UL
#define ALUout  0x10000UL
#define add_sub 0x20000UL //1 add, 0 sub
#define FI      0x40000UL //flag register (carry) <- saida do ALU

// ---------- op codes (o indice da tabela abaixo TEM que ser igual ao opcode) ----------
#define OP_NOP  0x0
#define OP_LDA  0x1   // A <- [addr]
#define OP_ADD  0x2   // A <- A + [addr]
#define OP_SUB  0x3   // A <- A - [addr]
#define OP_STA  0x4   // [addr] <- A
#define OP_LDI  0x5   // A <- imediato
#define OP_JMP  0x6   // PC <- addr
#define OP_OR   0x7   // A <- A | [addr]
#define OP_AND  0x8   // A <- A & [addr]
#define OP_XOR  0x9   // A <- A ^ [addr]
#define OP_JC   0xA   // se carry = 1: PC <- addr
#define OP_OUT  0xE   // OUT <- A
#define OP_HLT  0xF

// ---------- ciclo de busca ----------
#define T0 (PO | MI)
#define T1 (RO | II | PE)

// 16 instrucoes x 6 passos
const uint32_t microcodigo[16][6] =
{
  /* 0x0 NOP */ { T0, T1, 0, 0, 0, 0 },
  /* 0x1 LDA */ { T0, T1, IO | MI, RO | AI, 0, 0 },
  /* 0x2 ADD */ { T0, T1, IO | MI, RO | BI, ALUout | AI | add_sub | FI, 0 },
  /* 0x3 SUB */ { T0, T1, IO | MI, RO | BI, ALUout | AI | FI, 0 },
  /* 0x4 STA */ { T0, T1, IO | MI, AO | RI, 0, 0 },
  /* 0x5 LDI */ { T0, T1, IO | AI, 0, 0, 0 },
  /* 0x6 JMP */ { T0, T1, IO | JMP, 0, 0, 0 },
  /* 0x7 OR  */ { T0, T1, IO | MI, RO | BI, ALUout | AI | ALU_0, 0 },
  /* 0x8 AND */ { T0, T1, IO | MI, RO | BI, ALUout | AI | ALU_1, 0 },
  /* 0x9 XOR */ { T0, T1, IO | MI, RO | BI, ALUout | AI | ALU_0 | ALU_1, 0 },
  /* 0xA JC  */ { T0, T1, IO | JMP, 0, 0, 0 },   // so salta com carry = 1 (ver palavraFinal)
  /* 0xB     */ { T0, T1, 0, 0, 0, 0 },
  /* 0xC     */ { T0, T1, 0, 0, 0, 0 },
  /* 0xD     */ { T0, T1, 0, 0, 0, 0 },
  /* 0xE OUT */ { T0, T1, AO | OI, 0, 0, 0 },
  /* 0xF HLT */ { T0, T1, HLT, 0, 0, 0 }
};

// Endereco da EEPROM (11 bits):
//   bit 10    = condicao (flag)  -> gravamos as duas copias (0 e 1)
//   bits 9..6 = opcode
//   bits 5..0 = passo (T0..T5) vindo das saidas Y0..Y5 do 74LS138 (ativas em LOW):
//               passo k -> bit k = 0 e os outros 5 bits = 1
uint16_t montarEndereco(uint8_t cnd, uint8_t opcode, uint8_t passo)
{
  uint16_t campoPasso = (~(1u << passo)) & 0x3F;
  return ((uint16_t)(cnd & 1) << 10) | ((uint16_t)(opcode & 0x0F) << 6) | campoPasso;
}

void colocarEndereco(uint16_t endereco)
{
  for (uint8_t i = 0; i < 11; i++)
    digitalWrite(pinosNANO[i], (endereco >> i) & 1);
}

void liberarPinos() // deixa os pinos em alta impedancia para o computador dirigir o endereco
{
  for (uint8_t i = 0; i < 11; i++)
    pinMode(pinosNANO[i], INPUT);
}

bool enviarPacote(uint8_t cmd, uint16_t endereco, uint8_t dado)
{
  Wire.beginTransmission(ESCRAVO);
  Wire.write(cmd);
  Wire.write(highByte(endereco));
  Wire.write(lowByte(endereco));
  Wire.write(dado);
  return Wire.endTransmission() == 0;
}

// retorna 1 = gravou e verificou, 2 = falha na verificacao, 0 = timeout
uint8_t esperarStatus()
{
  unsigned long inicio = millis();
  while (millis() - inicio < TIMEOUT_MS)
  {
    if (Wire.requestFrom((uint8_t)ESCRAVO, (uint8_t)1) == 1)
    {
      uint8_t st = Wire.read();
      if (st != 0) return st;   // 0 = UNO ainda ocupado
    }
    delay(2);
  }
  return 0;
}

void imprimirHex(uint16_t v, uint8_t digitos)
{
  for (int8_t d = digitos - 1; d >= 0; d--)
    Serial.print((v >> (4 * d)) & 0xF, HEX);
}

// Palavra de controle que realmente vai para a EEPROM
uint32_t palavraFinal(uint8_t cnd, uint8_t op, uint8_t passo)
{
  uint32_t palavra = microcodigo[op][passo];

  // JC: com carry = 0 (cnd = 0) o passo T2 nao faz nada; so salta com carry = 1
  if (op == OP_JC && cnd == 0 && passo >= 2)
    palavra = 0;

  // HLT e ativo em LOW: em TODA palavra o bit HLT fica 1 (rodando) e so vira 0
  // quando a instrucao pede parada. O XOR faz isso para todas as linhas de uma vez.
  return palavra ^ HLT;
}

void programar(uint8_t chip) // chip = 1, 2 ou 3
{
  uint16_t total = 0, erros = 0;
  const uint8_t deslocamento = 8 * (chip - 1);

  for (uint8_t cnd = 0; cnd < 2; cnd++)
    for (uint8_t op = 0; op < 16; op++)
      for (uint8_t passo = 0; passo < 6; passo++)
      {
        uint16_t endereco = montarEndereco(cnd, op, passo);
        uint8_t dado = (uint8_t)((palavraFinal(cnd, op, passo) >> deslocamento) & 0xFF);

        colocarEndereco(endereco);
        delayMicroseconds(10);          // endereco estabiliza antes da escrita

        uint8_t st = 0;
        if (enviarPacote(CMD_GRAVAR, endereco, dado))
          st = esperarStatus();

        total++;
        if (st != 1) erros++;

        imprimirHex(endereco, 3); Serial.print(": ");
        imprimirHex(dado, 2);
        Serial.println(st == 1 ? F("  ok") : (st == 2 ? F("  ERRO verificacao") : F("  ERRO comunicacao")));
      }

  Serial.println(F("======PROGRAMACAO FINALIZADA======"));
  Serial.print(total); Serial.print(F(" enderecos, ")); Serial.print(erros); Serial.println(F(" erros"));
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(I2C_CLOCK_HZ);

  Serial.println(F("Qual EEPROM? 1 (bits 0-7), 2 (bits 8-15) ou 3 (bits 16-23):"));
  int chip = 0;
  while (chip < 1 || chip > 3)
  {
    if (Serial.available())
      chip = Serial.read() - '0';   // ignora Enter e outros caracteres
  }
  Serial.print(F("Gravando EEPROM ")); Serial.println(chip);

  for (uint8_t i = 0; i < 11; i++)
    pinMode(pinosNANO[i], OUTPUT);

  programar((uint8_t)chip);

  enviarPacote(CMD_LIBERAR, 0, 0);   // UNO solta os pinos
  esperarStatus();
  liberarPinos();
}

void loop() {}
