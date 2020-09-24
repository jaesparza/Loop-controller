#ifndef _MODE_H
#define _MODE_H

#include "../../HardwareConfig.h"
#include "../hwControl/Input.h"
#include "../hwControl/StepperMotor.h"
#include "../hwControl/UI.h"

class Mode {
  private:
  protected:
    UI *display = 0;
    StepperMotor *stepper = 0;
    Input *userInput = 0;
    long limitMin = 0;
    long limitMax = 0;

    bool checkLimits();

    uint8_t operateMotor(int speed, uint8_t CW, uint8_t CCW) {

        uint8_t motorMoved = false;
        stepper->setSpeed(speed);

        if (CW) {
            stepper->enableMotor();
            stepper->rotateCW();
            motorMoved = true;

        } else if (CCW) {

            stepper->enableMotor();
            stepper->rotateCCW();
            motorMoved = true;

        } else {
            stepper->disableMotor();
            motorMoved = false;
        }

        if (speed == SLOW) {
            delay(OPERATION_DELAY_SLOW);
        } else {
            delay(OPERATION_DELAY_FAST);
        }
        return motorMoved;
    }

  public:
    virtual void execute() = 0;
};

#endif // _MODE_H