#ifndef _MODE_OPERATE_ENCODER_H
#define _MODE_OPERATE_ENCODER_H

#include "Mode.h"

#include <Arduino.h>

class ModeOperateEncoder : public Mode {

  private:
    uint8_t updatePending = false;

    int getCount() {
        return analogRead(ENCODER);
    }

    bool checkLimits() {
        bool isWithinLimits = false;
        if (userInput->isRotateCW()) {
            isWithinLimits = ((getCount() > limitMin) ? true : false);

        } else if (userInput->isRotateCCW()) {
            isWithinLimits = ((getCount() < limitMax) ? true : false);
        }
        return isWithinLimits;
    }

  public:
    virtual void execute() {
        uint8_t moved = false;

        userInput->readInputs();
        display->update(getCount());

        if (checkLimits()) {
            moved = operateMotor(userInput->getSpeed(), userInput->isRotateCW(),
                                 userInput->isRotateCCW());
        }

        if (moved) {
            display->updateRefreshCount();

        } else {
            display->updateImmediate();
        }
    }

    ModeOperateEncoder(UI *disp, StepperMotor *stp, Input *ui,
                       long encoderLimitMin, long encoderLimitMax) {
        display = disp;
        stepper = stp;
        userInput = ui;
        limitMin = encoderLimitMin;
        limitMax = encoderLimitMax;
    }
};

#endif