/* 
 * Project: Remote controller v2
 * Author: ja - jaesparza@gmail.com
 * Description: Remote control of a stepper motor.
*/

#include <stdlib.h>
#include <string.h>

const int bSize = 50; 

#define DEBUG_1 3
#define DEBUG_2 8
#define DEBUG_3 12

#define SERIAL Serial1

// Hardware connections
// Connection to the motor driver
#define ENABLE_PIN    5
#define STEP_PIN      6
#define DIRECTION_PIN 7

// Microstep connection to the controller
#define MS1_PIN       9     
#define MS2_PIN       4
#define MS3_PIN       2

// XBEE sleep pin
#define SLEEP_PIN     10

// On board RX led pin
#define RXLED         17

// Motor control definitions
#define MOTOR_ENABLE    LOW
#define MOTOR_DISABLE   HIGH
#define SLOW            1
#define FAST            0

#define XBEE_ON         LOW
#define XBEE_OFF        HIGH

#define CCW             HIGH
#define CW              LOW

char Buffer[bSize];  // Serial buffer
char Command[10];    // Arbitrary Value for command size
char Data[15];       // ditto for data size
int ByteCount;
bool fastMode = false;


int ret = 0;
char * cmd = "a";
   
void SerialParser(void) {
//
//  One command per line.  Eventually, Data may have multiple 
//   fields separated by ":"
//  Command Format: "up to 5 Letter command, up to 10 letter data<\n>"
//                  No checking.
//
//  count will  be below Zero on a timeout.
//  read up to X chars or until EOT - in this case "\n" 
   ByteCount = -1;
   ByteCount =  SERIAL.readBytesUntil('\n',Buffer,bSize);  
    
   if (ByteCount  > 0) {
        strcpy(Command,strtok(Buffer,","));
                   
        strcpy(Data,strtok(NULL,","));     
   }
   memset(Buffer, 0, sizeof(Buffer));   // Clear contents of Buffer
   SERIAL.flush();
}

void clearBuffer() {
    strcpy(Command,"");
}

void disableStepper()
{
  digitalWrite(ENABLE_PIN, MOTOR_DISABLE); 
}

void enableStepper()
{
  digitalWrite(ENABLE_PIN, MOTOR_ENABLE);
}

void setup()
{
  // Set the pin direction for the peripherals
  // Pin direction for motor control signals
  pinMode(ENABLE_PIN,     OUTPUT);
  pinMode(STEP_PIN,       OUTPUT);
  pinMode(DIRECTION_PIN,  OUTPUT);
  pinMode(MS1_PIN,        OUTPUT);
  pinMode(MS2_PIN,        OUTPUT);
  pinMode(MS3_PIN,        OUTPUT);
  
  // Pin direction for RX led
  pinMode(RXLED,      OUTPUT);
  // Pin direction for sleep pin in XBee
  pinMode(SLEEP_PIN,  OUTPUT);

  digitalWrite(MS1_PIN,HIGH);
  digitalWrite(MS2_PIN,HIGH);
  digitalWrite(MS3_PIN,HIGH);

  pinMode(DEBUG_1, OUTPUT);
  pinMode(DEBUG_2, OUTPUT);
  digitalWrite(DEBUG_1, LOW);   

  //digitalWrite(SLEEP_PIN,XBEE_OFF);
  enableStepper();

  digitalWrite(DIRECTION_PIN, CW);

  // Initialize serial ports
  Serial1.begin(9600); // Serial through exposed RX/TX, hardware UART
                       // Attached to XBee, 
  
  // Serial over USB (Serial Monitor) -- Do not use while powered externally!
   Serial.begin(9600);
   Serial.println("Loop initialized");
}

void customStep(const int motorDelay)
{
  digitalWrite(STEP_PIN,LOW);
  delay(motorDelay);
  digitalWrite(STEP_PIN,HIGH);
  delay(motorDelay); 
}

void step() 
{
  digitalWrite(STEP_PIN,LOW);
  if (fastMode) 
  {
     delay(1); 
  }
  else 
  {
    delay(10);
  }
  digitalWrite(STEP_PIN,HIGH);
  if (fastMode)
  {
    delay(1); 
  }
  else 
  {
    delay(10);
  }
}
void ledToggle()
{
  digitalWrite(RXLED, LOW);   // set the RX LED ON
  digitalWrite(RXLED, HIGH);    // set the RX LED OFF
}

byte stateWord = 0;
char stateWord2 = 0;

bool done = false;

const int bufferSize = 10;

char buffer[bufferSize];

void clearBuffer(char * buf,int bufSize){
  for(int i =0; i<bufSize; i++) {
    buffer[i] = 0;
  }
}


void loop()
{
digitalWrite(DEBUG_2, LOW); 
    SerialParser();

    switch (Command[0]) {
      case 's':
        //SERIAL.println("Slow");
        //step(100);
        fastMode = false;
        break;
      case 'f':
        //SERIAL.println("Fast");
        //step(10);
        fastMode = true;
        break;
      case 'w': // CCW mode
        digitalWrite(DIRECTION_PIN, CCW);
        step();
        //step(atoi(Data));
        break;
      case 'c':
        digitalWrite(DIRECTION_PIN, CW);
        step();
      default:
        break;
    }
    
    clearBuffer();
    digitalWrite(DEBUG_2, HIGH); 
  
}
