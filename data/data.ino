//Librerías
#include <LiquidCrystal_I2C.h>

//Pines
#define PIN_OUT 9

//Pantalla
LiquidCrystal_I2C lcd(0x26,16,2);

//Variables
unsigned long oldTime;
unsigned long currentTime;
byte state;
int remaining_time;
byte coins;
byte coin;

byte aux;
int count;
char buffer[16]="";               //Buffer de la cadena donde se devuelve todo, número formateado y cadena concatenada

//Estados
#define WAITING 1
#define MAKING  2

//Monedas
#define CINCUENTA_CENTAVOS 1
#define UN_PESO 2
#define DOS_PESOS 3
#define CINCO_PESOS 4
#define DIEZ_PESOS 5

void setup(){
  //Serial.begin(9600);
  randomSeed(millis());
  lcd.init();
  lcd.backlight();
  pinMode(PIN_OUT,OUTPUT);
  INICIO();
}
void INICIO(){
  remaining_time=random(5,150);
  state=WAITING;
}

void loop(){
  currentTime=millis();
  switch(state){
    case WAITING:
    waiting();
    break;
    case MAKING:
    making();
    break;
  }
}

void waiting(){
  if((unsigned long)(currentTime-oldTime)>1000){
     remaining_time--;
     if(remaining_time==0)state=MAKING;
     oldTime=currentTime;
     lcd.setCursor(0,0);
     sprintf(buffer," %10d ",(remaining_time));
     lcd.print(buffer);
     //Serial.println(remaining_time);
     
  }
}

void making(){
  coins=random(1,4);
  //Serial.print("coins ");
  //Serial.print(coins);
  //Serial.println();
  for(; coins>0; coins--){
    coin=random(1,5);
    //Serial.print("coin");
    //Serial.print(coin);
    //Serial.println();
    switch(coin){
      case CINCUENTA_CENTAVOS:
      aux=1;
      count+=aux;
      break; 

      case UN_PESO:
      aux=2;
      count+=aux;
      break;

      case DOS_PESOS:
      aux=4;
      count+=aux;
      break;

      case CINCO_PESOS:
      aux=10;
      count+=aux;
      break;

      case DIEZ_PESOS:
      aux=20;
      count+=aux;
      break;
    }
    //Serial.print("aux ");
    //Serial.print(aux);
    //Serial.println();
    for(aux; aux>0; aux--){
      digitalWrite(PIN_OUT, HIGH);
      delay(50);
      digitalWrite(PIN_OUT, LOW);
      delay(50);
    }
    
  }
  lcd.setCursor(0,1);
  sprintf(buffer," %10d ",(count));
  lcd.print(buffer);
  INICIO();
}

