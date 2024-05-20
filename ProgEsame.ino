#include <dht11.h>
#include <LiquidCrystal.h>
#include <FastLED.h>
#define LED_PIN     2
#define NUM_LEDS    6
#define ON 1
#define OFF 0
#define LuminositaMin 1000
#define TempMax 20
#define UmidMin 50

CRGB leds[NUM_LEDS];

#include <dht11.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
dht11 DHT11;
int PinPompa=5;
int PinLuci=2;
int PinVentole=3;
int PinDht=4;
int SensLuce=A1;
int PinUmid=A0;
int s=0;
void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(PinPompa, OUTPUT);
  pinMode(PinLuci, OUTPUT);
  pinMode(PinVentole, OUTPUT);
  pinMode(PinDht, INPUT);
  pinMode(PinUmid, INPUT);
  pinMode(SensLuce, INPUT);
}

void loop() {

  ControlloTemp();
  ControlloLuce();
  ControlloUmid();
  
  delay(1000);
}
//FUNZIONI GESTIONE SENSORI

void ControlloTemp(){

  int chk = DHT11.read(PinDht);
  float temp = DHT11.temperature;
  if (chk == 0) {
  lcd.setCursor(0, 0);
  lcd.print("temperatura");
  lcd.print(":");
	lcd.print(temp, 1);
    
    if (temp > TempMax) {
      Ventole(ON);
    } 
    else {
      Ventole(OFF);
    }
  } 
}

void ControlloLuce(){
  float lumin = analogRead(A1);
  Serial.println(lumin);
  if(lumin<LuminositaMin){
    Luci(ON);
  }
  else{
    Luci(OFF);
  }
}

void ControlloUmid(){
  float umid = map((analogRead(PinUmid)), 0, 786, 0, 100);
  Serial.println(umid);
  lcd.setCursor(0, 1);
  lcd.print("umidita'"); 
  lcd.print(":");
  lcd.print(umid);
  lcd.print('%');
  if(umid<UmidMin){
    Pompa(ON);
  }
  else{
    Pompa(OFF);
  }
}
//FUNZIONI GESTIONE OUTPUT

void Pompa(char EnPompa){
    switch(EnPompa){
      case OFF: //pompa off
            digitalWrite(PinPompa, LOW);
            break;

      case ON: //pompa on
            digitalWrite(PinPompa, HIGH);
            delay(1000);
            digitalWrite(PinPompa, LOW);
            delay(10000);
            break;
            
    }
}

void Ventole(char EnVentole){
    switch(EnVentole){
      case OFF: //ventole off
            digitalWrite(PinVentole, LOW);
            break;

      case ON: //ventole on
            digitalWrite(PinVentole, HIGH);
            break;
            
    }
}

void Luci(char EnLuci){
    switch(EnLuci){
      case OFF: //Luci off
          for (int i = 0; i <= 166; i++) {         
            leds[i] = CRGB ( 0, 0, 0); 
            FastLED.show();
            delay(5);
            break;
          }
      case ON: //Luci on
          for (int i = 0; i <= 166; i++) {         
            leds[i] = CRGB (244, 253, 255); 
            FastLED.show();
            delay(5);
            break;
          }
    }
}

