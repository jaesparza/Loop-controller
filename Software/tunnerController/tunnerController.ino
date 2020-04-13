

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "HardwareConfig.h"
#include "UI.h"

#define MOTOR_ENABLE 0
#define MOTOR_DISABLE 1
#define SLOW 	1
#define FAST 	0

#define PUSHED   0
#define RELEASED 1

LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);

boolean cMode = false;
boolean calibrationComplete = false;

volatile long rotationCount = 0;

int speedIn = 0;
int cwIn = 0;
int ccwIn = 0;
int extraPB = 0;

void updateScreen(int position) {
  // Max position is 0 - 15
  //lcd.clear();
  if (position == 0){
    makeEmptyBar(1,16);
  }
  if ((position > 0 ) && (position < 15)) {
    lcd.setCursor(0,0);
    lcd.write(LEFT_DELIMITER);
    for(int i=1;i<position+1;i++) {
      lcd.setCursor(i,0);
      lcd.write(POSITION_BAR);
    }
    for(int j=position+1;j<15;j++) {
      lcd.setCursor(j,0);
      lcd.write(EMPTY_CHARACTER);
    }
      lcd.setCursor(15,0);
      lcd.write(EMPTY_RIGHT);
  }
  if (position == 15) {
    makeFullBar();
  }
}

void initLCD() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.createChar(SOLID_BLOCK, solidBlock);
  lcd.createChar(LEFT_DELIMITER, leftDelimiter);
  lcd.createChar(RIGHT_DELIMITER, rightDelimiter);
  lcd.createChar(POSITION_BAR, positionBar);
  lcd.createChar(EMPTY_LEFT, emptyLeft);
  lcd.createChar(EMPTY_RIGHT, emptyRight);
  lcd.createChar(EMPTY_CHARACTER, emptyCharacter);
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

void setup() {

  // Initialize hardware
  initLCD();
  initIO();
  initMotorState();
  initSerial();

  // Initialize UI
  //makeFullBar();
 // makeEmptyBar(1,16);
  delay(400);

  // Check inputs and enter configuration configuration mode if requested
  readInputs();
  if (extraPB==PUSHED) {
    cMode = true;
  }

// for(int i= 0; i<16;i++) {
//   updateScreen(i);
//   delay(1000);
//  }
}

void makeFullBar(){
  lcd.setCursor(0,0);
  lcd.write(LEFT_DELIMITER);

  for(int i=1;i<15;i++) {
    lcd.setCursor(i,0);
    lcd.write(POSITION_BAR);
  }

  lcd.setCursor(15,0);
  lcd.write(RIGHT_DELIMITER);
}

void makeEmptyBar(int start, int last) {
  lcd.setCursor(0,0);
  lcd.write(LEFT_DELIMITER);

  for(int i = start;i<last;i++) {
    lcd.setCursor(i,0);
    lcd.write(EMPTY_CHARACTER);
  }

  lcd.setCursor(15,0);
  lcd.write(EMPTY_RIGHT);
}

bool storeMaxCount(int maxCount) {

  return true;
}

void sendPulse(int orientation) {

    int duration = 0;
    if (speedIn == SLOW) {
       duration = 10;
       if (orientation ==ROTATE_CW){
          rotationCount = rotationCount + 1;
       }
       else {
         rotationCount = rotationCount - 1;
       }
    }
    else
    {
       duration = 0;
       if (orientation ==ROTATE_CW){
          rotationCount = rotationCount + 10;
       }
       else {
         rotationCount = rotationCount - 10;
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

        //updateScreen(1);
       } // No need to re-evaluate cMode
    }
}

void configuration() {
  lcd.clear(); // This has to be executed once...
  lcd.setCursor(0,0);
  lcd.print(CONFIG_MESSAGE);

   // ask to release button and wait for that
   // to happen
  waitForRelease();
  readInputs();
  if (extraPB == false) { 
    lcd.setCursor(0,1);
    lcd.print("Stored new limit");
    storeMaxCount(10); 
  }
}


boolean waitForRelease(){
  extraPB = digitalRead(BUTTON_1_IN);
  while(extraPB == LOW) {
      extraPB = digitalRead(BUTTON_1_IN);
      Serial.println("Waiting for release");
  }
  return true;
}

void normalOperation() {
  lcd.setCursor(0, 1);
  lcd.print(rotationCount);
  readInputs();

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

void clearLCDLine(int line)
{               
        lcd.setCursor(0,line);
        for(int n = 0; n < 16; n++) 
        {
                lcd.print(" ");
        }
}