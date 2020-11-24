#include <LiquidCrystal.h>

#include <Wire.h>

#define BOTAO 7
#define LED 6
#define SRCADDR 0x02

bool processar = false;
byte recebido = 0;

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
int backLight = 13;

unsigned long Tempo = 0;
unsigned long TempoOcioso = 0;

void setup()
{
  pinMode(BOTAO, INPUT);
  pinMode(LED, OUTPUT);
  Wire.begin(SRCADDR);
  Wire.onReceive(trataMsg);
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH);
  lcd.begin(16,2);
  lcd.clear();
  
  Serial.begin(9600);
}

void loop() 
{ 
  if (processar)
  {
    processar = false;
    if (recebido == 1)
    {
      digitalWrite(LED, HIGH);
    }
    else
    {
      digitalWrite(LED, LOW);
    }
  }
  if(digitalRead(LED) == HIGH){
    Tempo = millis() - TempoOcioso;
  }
  else{
    TempoOcioso = millis()- Tempo;
  }
  lcd.setCursor(0,0);
  lcd.print("Jogador 1");
  lcd.setCursor(0,1);
  if(Tempo/1000 < 10){
    lcd.print("00:0");
  	lcd.print(Tempo / 1000);
  }
  else{
    if(Tempo/1000 < 60){
      	lcd.print("00:");
  		lcd.print(Tempo / 1000);
    }
    else{
      if((Tempo/1000)/60 < 10){
        lcd.print("0");
        lcd.print((Tempo/1000)/60);
        if((Tempo/1000)%60 < 10){
          lcd.print(":0");
          lcd.print((Tempo/1000)%60);
        }
        else{
          lcd.print(":");
          lcd.print((Tempo/1000)%60);
        }
      }
      else{
        lcd.print((Tempo/1000)/60);
        if((Tempo/1000)%60 < 10){
          lcd.print(":");
          lcd.print((Tempo/1000)%60);
        }
        else{
          lcd.print((Tempo/1000)%60);
        }
      }
    }
  }
  
  delay(1000);
}

void trataMsg(int qtdBytes) {
  if (Wire.available()) {
    recebido = Wire.read();
    Serial.print("Escravo 1 Recebido: ");
    Serial.println((int)recebido);
    processar = true;
  }
}
