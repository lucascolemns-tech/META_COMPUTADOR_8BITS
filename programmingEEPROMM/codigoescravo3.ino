#include <Wire.h>

#define CE 10
#define OE 11
#define WE 12

uint16_t enderecoATUAL = 0;
uint8_t dadoATUAL = 0;
uint8_t dadoLIDO = 0;
bool pronto = false;

const byte pinosUNO[8] = {9,8,7,6,5,4,3,2};

uint8_t segmentos_anodo_comum[10] =
{
0xC0, // 0
0xF9, // 1
0xA4, // 2
0xB0, // 3
0x99, // 4
0x92, // 5
0x82, // 6
0xF8, // 7
0x80, // 8
0x90 // 9
};

void extrair_dado(byte dado)
{
/*
vamos escrever o dado recebido D0 a D7
completar ciclo de escrita
*/  
  for (int n = 0 ; n < 8 ; n++)
  {
  digitalWrite(pinosUNO[n], (dado >> n) & 1);
  }
}

void EEPROMM_dados(uint8_t dado)
{
  //definir dados como output para serem escritos
    for (int n1 = 0 ; n1 < 8 ; n1++)
    {   
    pinMode(pinosUNO[n1], OUTPUT); 
    }
      delay(5);

extrair_dado(dado);

  //ciclo de escrita 
  digitalWrite(CE, LOW);
  digitalWrite(WE, LOW);
  digitalWrite(OE, HIGH);

  delay(5);
  
  digitalWrite(WE, HIGH);
  digitalWrite(CE, HIGH);

  delay(10);
}

void EEPROMM_leitura(uint16_t endereco, uint8_t dadoReal)
{
  //definir dados como input para serem lidos
    for (int n1 = 0 ; n1 < 8 ; n1++)
    {   
    pinMode(pinosUNO[n1], INPUT); 
    }
    delay(5);
  //ciclo leitura
  digitalWrite(CE, LOW);
  digitalWrite(OE, LOW);   // Ativa saída
  digitalWrite(WE, HIGH);
    
  uint8_t leitura1 = 0;
  uint8_t leitura2 = 0;

  delayMicroseconds(5);

  for (int i = 0; i < 8; i++)
    leitura1 |= digitalRead(pinosUNO[i]) << i;
   
  delayMicroseconds(5);
  
  for (int i = 0; i < 8; i++) 
    leitura2 |= digitalRead(pinosUNO[i]) << i;

  if (leitura1 == leitura2)
    dadoLIDO = leitura1;
  else
    dadoLIDO = 0xFF;
       
  if (dadoReal == dadoLIDO)
  {
    Serial.print(dadoLIDO, HEX);
    Serial.print(" ");
  }
  else if (dadoReal != dadoLIDO)
    Serial.print("xx ");

  if ((endereco % 8) == 7)
  {
    Serial.print(" : ");
    Serial.print(endereco+1);
    Serial.println(); 
  }
    delay(100);
    digitalWrite(OE , HIGH);
    digitalWrite(CE , HIGH);
  }

void EEPROMM_display7seg(uint16_t endereco, uint8_t dado)
{
int display = endereco / 256;
uint8_t numero;
  /*
  0 - 255    --   display 1 
  256 - 511  --   display 2 
  512 - 767  --   display 3
  768 - 1023 --   display 4
  */

  if (display < 1)
    numero = (dado % 10);

  else if (display >= 1 && display < 2)
    numero = (dado % 100) / 10;

  else if (display >= 2 && display < 3)
    numero = (dado % 1000) / 100; 

  else if (display >= 3)
    numero = 0;

dadoATUAL = numero; //dado a ser escrito no endereço da EEPROMM
}

void operacao_finalizada()
{
  if (pronto == false)
    Wire.write(0);

  if (pronto == true)
  {
    Wire.write(1);
    pronto = false;
  }
}
void receberEventos_Nano(uint8_t bytes)
{
/*
chegam quatro bytes, o de incialização (1), os 8 bits mais significativos do endereco, os menos significativos 
e os 8 bits do dado calculado
*/
  if (bytes != 4)
  return;

//no caso aq é o comando q você define, nos mandamos o comando 1 pra incilizar as funções, mas podem haver qnts forem necessários
  byte check = Wire.read();
  if (check != 1)
  return;

  uint16_t endereco = Wire.read() << 8;
  endereco |= Wire.read();
    enderecoATUAL = endereco;
  
  uint8_t dado = Wire.read();

EEPROMM_display7seg(endereco, dado);

uint8_t dadoReal = segmentos_anodo_comum[dadoATUAL];
  EEPROMM_dados(dadoReal);

  delay(5);

  EEPROMM_leitura(endereco, dadoReal); 

  if (endereco >= 1023)
    {
      digitalWrite(CE, LOW);
      digitalWrite(OE, LOW);
      digitalWrite(WE, HIGH);
    }
  
  pronto=true;
}

void setup() 
{
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onReceive(receberEventos_Nano);
  Wire.onRequest(operacao_finalizada);

  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(WE, OUTPUT);

  digitalWrite(CE , HIGH);
  digitalWrite(OE , HIGH);
  digitalWrite(WE , HIGH);
}

void loop() 
{
  

}


