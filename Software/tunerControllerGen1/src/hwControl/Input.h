#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

// The push-buttons have external pull-ups, therefore signals are:
#define PUSHED   0
#define RELEASED 1

class Input {
  public:
    int getSpeed();
    int getCwIn();
    int getCcwIn();
    int getExtraPB();
    void readInputs();
    void initInput();

    uint8_t isRotateCCW();
    uint8_t isRotateCW();
    uint8_t CwAndCCWPushed();

    static Input *getInstance();

  private:
    int speedIn = 0;
    int cwIn = 0;
    int ccwIn = 0;
    int extraPB = 0;

    static Input *instance;
    Input();
};

#endif // INPUT_H