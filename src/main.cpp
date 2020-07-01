#include "Arduino.h"


#define IRLED 6
#define LED 7
#define Piezo A0
#define Poty A2
#define Button 11

int threshhold = 800;
int PiezoIN = 0;
int PotyIN = 0;
int ButtonCheck = 0;
int timer=0;


void takePhoto(void);

void setup() {

  pinMode(IRLED, OUTPUT); 
  pinMode(LED, OUTPUT); 
  pinMode(Button, INPUT); 
  digitalWrite(LED, LOW);
  // Serial.begin(9600);
}

void loop() {

  PiezoIN = analogRead(Piezo); //reading the piezo
  // Serial.println("PiezoIN");
  // Serial.println(PiezoIN);

  ButtonCheck = digitalRead(Button); //reading the button
  // Serial.println("ButtonCheck");
  // Serial.println(ButtonCheck);
  // Serial.println("threshhold");
  // Serial.println(threshhold);

  if(ButtonCheck == HIGH){ //if button is pressed the threshhold wil be set to poty input
    PotyIN = analogRead(Poty);
    // Serial.println("PotyIN");
    // Serial.println(PotyIN);
    threshhold = PotyIN;
    digitalWrite(LED, HIGH);
  }else{
    digitalWrite(LED, LOW);
  }

  if(PiezoIN <= threshhold){ //if the piezo input is lower than the threshhold a photo gets triggered
    takePhoto();
    delay(1000);
  }
  
  if(timer>=6000){ //counting seconds up to 10 min
    takePhoto();
    timer=0;
  }

  delay(100);
  timer++;
  //Serial.println(timer);
  
}



void takePhoto(void) { //function to trigger a photo via IR LED on a Nikon camera
  int i;
  // Serial.println("foto");
  timer=0;

  for (i = 0; i < 76; i++) {
    digitalWrite(IRLED, HIGH);
    delayMicroseconds(7);
    digitalWrite(IRLED, LOW);
    delayMicroseconds(7);
  }
  delay(27);
  delayMicroseconds(810);
  for (i = 0; i < 16; i++) {
    digitalWrite(IRLED, HIGH);
    delayMicroseconds(7);
    digitalWrite(IRLED, LOW);
    delayMicroseconds(7);
  }
  delayMicroseconds(1540);
  for (i = 0; i < 16; i++) 
  {
    digitalWrite(IRLED, HIGH);
    delayMicroseconds(7);
    digitalWrite(IRLED, LOW);
    delayMicroseconds(7);
  }
  delayMicroseconds(3545);
  for (i = 0; i < 16; i++) {
    digitalWrite(IRLED, HIGH);
    delayMicroseconds(7);
    digitalWrite(IRLED, LOW);
    delayMicroseconds(7);
  }

}
