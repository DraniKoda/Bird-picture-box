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
int timerms=0;
int timers=0;

void takePhoto(void);

void setup() {

  pinMode(IRLED, OUTPUT); 
  pinMode(LED, OUTPUT); 
  pinMode(Button, INPUT); 
  digitalWrite(LED, LOW);
  //Serial.begin(9600);

  TCCR0A=(1<<WGM01);    //Set the CTC mode   
  OCR0A=0xF9; //Value for ORC0A for 1ms 
  TIMSK0|=(1<<OCIE0A);   //Set the interrupt request
  sei(); //Enable interrupt
  TCCR0B|=(1<<CS01);    //Set the prescale 1/64 clock
  TCCR0B|=(1<<CS00);

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
  if(timerms>=1000){ //counting ms and adding to seconds counter
    timerms=0;
    timers++;
  }
  if(timers>=600){ //counting seconds up to 10 min
    takePhoto();
    timers=0;
  }

}

ISR(TIMER0_COMPA_vect){    //This is the interrupt request
  timerms++;
}

void takePhoto(void) { //function to trigger a photo via IR LED on a Nikon camera
  int i;
  //Serial.println("foto");
  timers=0;

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
