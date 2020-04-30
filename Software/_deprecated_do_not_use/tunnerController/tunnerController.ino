#include <Arduino.h>
#include "HardwareConfig.h"
#include "UI.h"

#define MOTOR_ENABLE 0
#define MOTOR_DISABLE 1
#define SLOW 	1
#define FAST 	0

#define PUSHED   0
#define RELEASED 1

boolean cMode = false;
boolean calibrationComplete = false;

volatile long rotationCount = 0;

int speedIn = 0;
int cwIn = 0;
int ccwIn = 0;
int extraPB = 0;

int lastRefresh = 0;

void setup() {

  // Initialize hardware
  initLCD();
  initIO();
  initMotorState();
  initSerial();

  // Initialize UI
  // makeFullBar();
  // makeEmptyBar(1,16);

  showText();

  delay(400);

  // Check inputs and enter configuration configuration mode if requested
  readInputs();
  if (extraPB==PUSHED) {
    cMode = true;
  }

  // Some demo code to test the progress bar
  for(int i= 0; i<16;i++) {
   updateScreen(i);
   delay(50);
  }
  for(int i= 15; i>=0;i--) {
   updateScreen(i);
   delay(50);
  }

}

bool storeMaxCount(int maxCount) {

  return true;
}

void sendPulse(int orientation) {

    int duration = 0;
    if (speedIn == SLOW) {
       duration = DELAY_SLOW;
       if (orientation ==ROTATE_CW){
          rotationCount = rotationCount + 1;
       }
       else {
         rotationCount = rotationCount - 1;
       }
    }
    else
    {
       duration = DELAY_FAST;
       if (orientation ==ROTATE_CW){
          rotationCount = rotationCount + 1;
       }
       else {
         rotationCount = rotationCount - 1;
       }
    }
    digitalWrite(STEP_PIN,HIGH);
    delay(duration);
    digitalWrite(STEP_PIN,LOW);
    delay(duration);
}

void readInputs(){
  speedIn = digitalRead(SPEED);
  cwIn =    digitalRead(CW_IN);
  ccwIn =   digitalRead(CCW_IN);
  extraPB = digitalRead(BUTTON_1_IN);
}


void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):

    if (cMode == true) {
      while(1) { configuration(); } // No need to re-evaluate cMode
    }
    else {
      while(1) { 
        normalOperation(); 
        lastRefresh++;
        //updateScreen(1);
       } // No need to re-evaluate cMode
    }
}

void configuration() {
  //lcd.clear(); // This has to be executed once...
  //lcd.setCursor(0,0);
  //lcd.print(CONFIG_MESSAGE);
   // ask to release button and wait for that
   // to happen
  waitForRelease();
  readInputs();
  if (extraPB == false) { 

    storeMaxCount(10); 
  }
}

boolean waitForRelease(){
  extraPB = digitalRead(BUTTON_1_IN);
  while(extraPB == LOW) {
      extraPB = digitalRead(BUTTON_1_IN);
  }
  return true;
}

void normalOperation() {

  readInputs();
  updateCount(rotationCount);
  updateScreen(rotationCount/COUNT_PER_COL);
  operateMotor();
}

void operateMotor() {
  if ((cwIn == 1) && (ccwIn ==0)) {
      digitalWrite(ENABLE_PIN, MOTOR_ENABLE);
      digitalWrite(DIRECTION_PIN,HIGH);
      sendPulse(ROTATE_CW);
      clearLCDLine(2);
  }
  else if ((ccwIn == 1)&& (cwIn ==0)) {
      digitalWrite(DIRECTION_PIN,LOW);
      digitalWrite(ENABLE_PIN, MOTOR_ENABLE);
      sendPulse(ROTATE_CCW);
      clearLCDLine(2);
  }
  else {
    digitalWrite(ENABLE_PIN, MOTOR_DISABLE);
  }
}

void initIO() {
  pinMode(CW_IN, INPUT);
  pinMode(CCW_IN, INPUT);
  pinMode(SPEED, INPUT);
  pinMode(BUTTON_1_IN,INPUT);
  digitalWrite(BUTTON_1_IN, HIGH); // Enable the internal pull-ups

  pinMode(STEP_PIN,OUTPUT);
  pinMode(ENABLE_PIN,OUTPUT);
  pinMode(DIRECTION_PIN,OUTPUT);
}

void initMotorState() {
  digitalWrite(DIRECTION_PIN,HIGH);
}

void initSerial(){
  Serial.begin(9600);
  Serial.println("Motor driver initialized");
}