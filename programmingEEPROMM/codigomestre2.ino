#include <Wire.h>

#define ESCRAVO 8
#define CLOCK_MHZ 100000
//codigo mestre endereços: D2 to D12

bool listagem = false;
bool comecar = false;
unsigned long intervalo = 0;

const byte pinosNANO[11] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

void EEPROMM_endereco(uint16_t endereco, uint8_t dado)
{
  Wire.beginTransmission(ESCRAVO);
  
  Wire.write(1); //sinal de começo, qm tiver dúvida é preciso ver comunicação I2C é o padroa dos sinais dela
  
  Wire.write(highByte(endereco)); // ex: valor 1111 0000 vai mandar somente "1111" xxxx 
  Wire.write(lowByte(endereco)); // xxxx 0000 
  
  Wire.write(dado);

  Wire.endTransmission();

  byte prontoMestre = 0;
   
  while (prontoMestre == 0)
  {
    Wire.requestFrom(8,1);

    if (Wire.available())
    {
      prontoMestre = Wire.read();
      break;
    }
    if (millis() - intervalo >= 5000)
    {
      intervalo = millis();
      break;
    }
  } 

}

void setup() 
{
  
  Serial.begin(9600);

  //aguarda você digitar "r" para começar
  while (comecar == false)
  {
  char letra = Serial.read();
  if (letra == 'r' || letra == 'R')
    comecar = true;
  }

  Wire.begin();
  Wire.setClock(CLOCK_MHZ);
  
  for (int i=2; i <= 12; i++)
  {
  pinMode(i, OUTPUT);  

  }
}

void loop() 
{
  static uint16_t endereco = 0;

  for (int wr = 0; wr < 11; wr++)
  {
    digitalWrite(pinosNANO[wr], (endereco >> wr) & 1);
    Serial.print(digitalRead(pinosNANO[wr]));
  }
  Serial.println();

  uint8_t dado;
    if (endereco < 256)
      dado = endereco;
    else if(endereco < 512)
      dado = endereco - 256;
    else if (endereco < 768)
      dado = endereco - 512;
    else if (endereco < 1024)
      dado = endereco - 768;
   
  EEPROMM_endereco(endereco, dado);
  delay(100);

  endereco++;

if (endereco >= 1024)
  Serial.println("======PROGRAMACAO FINALIZADA======");

if (endereco >= 1024)
  {
    listagem = true;
    endereco = 0;
  } 

while (listagem)
  { 
  endereco++;
  for (int l = 0; l < 11; l++)
  {
    digitalWrite(pinosNANO[l], (endereco >> l) & 1);
    Serial.print(digitalRead(pinosNANO[l]));
  }
  delay(1250);
  }
}




