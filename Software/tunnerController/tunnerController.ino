

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "HardwareConfig.h"

#define MOTOR_ENABLE 0
#define MOTOR_DISABLE 1
#define SLOW 	1
#define FAST 	0

#define PUSHED   0
#define RELEASED 1

const int stepPin = 9;
const int enablePin = 8;

boolean cMode = false;


volatile long rotationCount = 0;

int speedIn = 0;
int cwIn = 0;
int ccwIn = 0;

LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);

byte solidBlock[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

void setup() {


  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Loop Tuner");

  lcd.createChar(0, solidBlock);

  pinMode(CW_IN, INPUT);
  pinMode(CCW_IN, INPUT);
  pinMode(SPEED, INPUT);
  Serial.begin(9600);

  pinMode(stepPin,OUTPUT);

  pinMode(enablePin,OUTPUT);
  pinMode(A1,OUTPUT);

  digitalWrite(A1,HIGH);

  delay(1000);
  readInputs();
  cMode = configMode();

}

bool configMode() {

  if (cwIn == 0) // pushed
  {
      lcd.setCursor(0,0);
      lcd.print("cfg - low limit");
      return true;
  }

  if (ccwIn == 0)
  {
      lcd.setCursor(0,0);
      lcd.print("cfg - high limit");
      return true;
  }

  return false;
}


void sendPulse() {

    int duration = 0;
    if (speedIn == SLOW) {
       duration = 10;
       rotationCount = rotationCount + 1;
    }
    else
    {
       duration = 0;
       rotationCount = rotationCount + 10;
    }
    digitalWrite(stepPin,HIGH);
    delay(duration);
    digitalWrite(stepPin,LOW);
    delay(duration);
}


void readInputs(){
  speedIn = digitalRead(SPEED);
  cwIn =  digitalRead(CW_IN);
  ccwIn =  digitalRead(CCW_IN);
}


void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):

    if (cMode == true) {

    }
    else {
      normalOperation();
    }
}

void configurationOperation() {

}

void normalOperation() {
    lcd.setCursor(0, 1);
  //lcd.write(byte(0));
  lcd.print(rotationCount);
  readInputs();

  if ((cwIn == 1) && (ccwIn ==0)) {
      digitalWrite(enablePin, MOTOR_ENABLE);
      digitalWrite(A1,HIGH);
      sendPulse();
  }
  else if ((ccwIn == 1)&& (cwIn ==0)) {
      digitalWrite(A1,LOW);
      digitalWrite(enablePin, MOTOR_ENABLE);
      sendPulse();
  }
  else {
    digitalWrite(enablePin, MOTOR_DISABLE);
  }
}

/*

  Serial.println();
  Serial.print("Speed is: ");
  Serial.print(digitalRead(SPEED));
  Serial.print(" CW is: ");
  Serial.print(digitalRead(CW_IN));
  Serial.print(" CCW is: ");
  Serial.print(digitalRead(CCW_IN));

  if( speedIn == SLOW) // SLOW
  {
      delay(1000);
  }
  else // FAST
  {
      delayMicroseconds(100);
  }

 */

