

#ifndef UI_H_
#define UI_H_

#define INIT_MESSAGE    "   Loop tunner"
#define CONFIG_MESSAGE  "CFG mode - LOW"


#define SOLID_BLOCK      0
#define LEFT_DELIMITER   1
#define RIGHT_DELIMITER  2
#define POSITION_BAR     3
#define EMPTY_LEFT       4
#define EMPTY_RIGHT      5
#define EMPTY_CHARACTER  6

byte solidBlock[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
};

byte rightDelimiter[8] = {
    B11111,
    B1,
    B11101,
    B11101,
    B11101,
    B11101,
    B1,
    B11111
};

byte leftDelimiter[8] = {
    B11111,
    B10000,
    B10111,
    B10111,
    B10111,
    B10111,
    B10000,
    B11111
};

byte positionBar[8] = {
    B11111,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111,
    B00000,
    B11111
};

byte emptyCharacter[8] = {
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111
};

byte emptyRight[8] = {
    B11111,
    B1,
    B1,
    B1,
    B1,
    B1,
    B1,
    B11111
};

byte emptyLeft[8] = {
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

#endif /* UI_H_ */
