

#ifndef UI_H_
#define UI_H_

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "HardwareConfig.h"


/* Custom character creator:
*  https://www.quinapalus.com/hd44780udg.html
*/

#define INIT_MESSAGE     "   Loop tunner"
#define CONFIG_MESSAGE   "CFG mode - LOW"
#define LINE_1_COUNT     "Position: "
#define LINE_1_COUNT_LEN 10

#define SOLID_BLOCK      0
#define LEFT_DELIMITER   1
#define RIGHT_DELIMITER  2
#define POSITION_BAR     3
#define EMPTY_LEFT       4
#define EMPTY_RIGHT      5
#define EMPTY_CHARACTER  6

static byte solidBlock[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
};

static byte rightDelimiterThin[8] = { 
    B11111,
    B00001,
    B11101,
    B11101,
    B11101,
    B00001,
    B11111
};

static byte leftDelimiterThin[8] = {
    B11111,
    B10000,
    B10111,
    B10111,
    B10111,
    B10000,
    B11111
};


static byte positionBarThin[8] = {
    B11111,
    B00000,
    B11111,
    B11111,
    B11111,
    B00000,
    B11111  
};

static byte rightDelimiter[8] = {
    B11111,
    B00001,
    B11101,
    B11101,
    B11101,
    B11101,
    B00001,
    B11111
};

static byte leftDelimiter[8] = {
    B11111,
    B10000,
    B10111,
    B10111,
    B10111,
    B10111,
    B10000,
    B11111
};

static byte positionBar[8] = {
    B11111,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111,
    B00000,
    B11111
};

static byte emptyCharacterThin[8] = {
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111
};

static byte emptyCharacter[8] = {
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111
};

static byte emptyRightThin[8] = {
    B11111,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B11111
};

static byte emptyLeftThin[8] = {
    B11111,
    B10000,
    B10100,
    B10100,
    B10100,
    B10100,
    B11111
};

static byte emptyRight[8] = {
    B11111,
    B1,
    B1,
    B1,
    B1,
    B1,
    B1,
    B11111
};

static byte emptyLeft[8] = {
    B11111,
    B10000,
    B10100,
    B10100,
    B10100,
    B10100,
    B10000,
    B11111
};



void updateScreen(int position);
void initLCD();
void makeFullBar();
void makeEmptyBar(int start, int last);
void clearLCDLine(int line);
void updateCount(int rotationCount);
void showText();
void writeNumber(char n);
void removeNullTermination(char * buffer,int len);

#endif /* UI_H_ */
