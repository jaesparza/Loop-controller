
#define SOLID_BLOCK     0
#define LEFT_DELIMITER  1
#define RIGHT_DELIMITER 2
#define POSITION_BAR    3
#define EMPTY_LEFT      4
#define EMPTY_RIGHT     5
#define EMPTY_CHARACTER 6

#include <Arduino.h>

/* clang-format off */
// Easier to see the character if they are not formatted by clang
static uint8_t solidBlock[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
};

static uint8_t rightDelimiterThin[8] = { 
    B11111,
    B00001,
    B11101,
    B11101,
    B11101,
    B00001,
    B11111
};

static uint8_t leftDelimiterThin[8] = {
    B11111,
    B10000,
    B10111,
    B10111,
    B10111,
    B10000,
    B11111
};


static uint8_t positionBarThin[8] = {
    B11111,
    B00000,
    B11111,
    B11111,
    B11111,
    B00000,
    B11111  
};

static uint8_t rightDelimiter[8] = {
    B11111,
    B00001,
    B11101,
    B11101,
    B11101,
    B11101,
    B00001,
    B11111
};

static uint8_t leftDelimiter[8] = {
    B11111,
    B10000,
    B10111,
    B10111,
    B10111,
    B10111,
    B10000,
    B11111
};

static uint8_t positionBar[8] = {
    B11111,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111,
    B00000,
    B11111
};

static uint8_t emptyCharacterThin[8] = {
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111
};

static uint8_t emptyCharacter[8] = {
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111
};

static uint8_t emptyRightThin[8] = {
    B11111,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B11111
};

static uint8_t emptyLeftThin[8] = {
    B11111,
    B10000,
    B10100,
    B10100,
    B10100,
    B10100,
    B11111
};

static uint8_t emptyRight[8] = {
    B11111,
    B1,
    B1,
    B1,
    B1,
    B1,
    B1,
    B11111
};

static uint8_t emptyLeft[8] = {
    B11111,
    B10000,
    B10100,
    B10100,
    B10100,
    B10100,
    B10000,
    B11111
};
/* clang-format on */
