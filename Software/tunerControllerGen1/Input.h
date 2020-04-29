#ifndef INPUT_H
#define INPUT_H

#include "HardwareConfig.h"
#include <Arduino.h>

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
    boolean isRotateCCW();
    boolean isRotateCW();
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