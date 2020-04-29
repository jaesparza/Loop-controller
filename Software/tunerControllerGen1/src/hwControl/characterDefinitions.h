// Used custom character creator from :
// https://www.quinapalus.com/hd44780udg.html

#define SOLID_BLOCK     0
#define LEFT_DELIMITER  1
#define RIGHT_DELIMITER 2
#define POSITION_BAR    3
#define EMPTY_LEFT      4
#define EMPTY_RIGHT     5
#define EMPTY_CHARACTER 6

#include <stdint.h>

/* clang-format off */
// Easier to see the characters if they are not formatted by clang
static uint8_t solidBlock[8] = {
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
};

static uint8_t rightDelimiterThin[8] = { 
    0b11111,
    0b00001,
    0b11101,
    0b11101,
    0b11101,
    0b00001,
    0b11111
};

static uint8_t leftDelimiterThin[8] = {
    0b11111,
    0b10000,
    0b10111,
    0b10111,
    0b10111,
    0b10000,
    0b11111
};


static uint8_t positionBarThin[8] = {
    0b11111,
    0b00000,
    0b11111,
    0b11111,
    0b11111,
    0b00000,
    0b11111  
};

static uint8_t rightDelimiter[8] = {
    0b11111,
    0b00001,
    0b11101,
    0b11101,
    0b11101,
    0b11101,
    0b00001,
    0b11111
};

static uint8_t leftDelimiter[8] = {
    0b11111,
    0b10000,
    0b10111,
    0b10111,
    0b10111,
    0b10111,
    0b10000,
    0b11111
};

static uint8_t positionBar[8] = {
    0b11111,
    0b00000,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b00000,
    0b11111
};

static uint8_t emptyCharacterThin[8] = {
    0b11111,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111
};

static uint8_t emptyCharacter[8] = {
    0b11111,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b11111
};

static uint8_t emptyRightThin[8] = {
    0b11111,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b00001,
    0b11111
};

static uint8_t emptyLeftThin[8] = {
    0b11111,
    0b10000,
    0b10100,
    0b10100,
    0b10100,
    0b10100,
    0b11111
};

static uint8_t emptyRight[8] = {
    0b11111,
    0b1,
    0b1,
    0b1,
    0b1,
    0b1,
    0b1,
    0b11111
};

static uint8_t emptyLeft[8] = {
    0b11111,
    0b10000,
    0b10100,
    0b10100,
    0b10100,
    0b10100,
    0b10000,
    0b11111
};
/* clang-format on */
