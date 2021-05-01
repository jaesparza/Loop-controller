#ifndef _MODE_OPERATE_ENCODER_H
#define _MODE_OPERATE_ENCODER_H

#include "Mode.h"

#include <Arduino.h>

class ModeOperateEncoder : public Mode {

  private:
    uint8_t updatePending = false;

    int encoderCountFiltered = 0;

    int getCount() {
        return analogRead(ENCODER);
    }

    int updateCount() {
        // encoderCountFiltered = (encoderCountFiltered + getCount()) / 2;
        encoderCountFiltered = getCount();
    }

    bool checkLimits() {
        bool isWithinLimits = false;

        updateCount();

        int rawCount = encoderCountFiltered;

        /*
        if ((rawCount >= limitMin) && (rawCount <= limitMax)) {
            isWithinLimits = true;
        } else {
            isWithinLimits = false;
        }
        */

        if (userInput->isRotateCW()) {
            isWithinLimits = ((rawCount > limitMin) ? true : false);

        } else if (userInput->isRotateCCW()) {
            isWithinLimits = ((rawCount < limitMax) ? true : false);
        }

        return isWithinLimits;
    }

  public:
    virtual void execute() {
        uint8_t moved = false;

        userInput->readInputs();

        display->updatePositionEnc(
            getCount()); // Update function to be used with encoder
        // display->update(getCount()); // Update function based on counts

        if (checkLimits()) {
            moved = operateMotor(userInput->getSpeed(), userInput->isRotateCW(),
                                 userInput->isRotateCCW());
        } else {
            stepper->disableMotor();
        }

        if (moved) {
            display->updateRefreshCount();

        } else {
            display->updateImmediate();
            stepper->disableMotor();
        }
    }

    ModeOperateEncoder(UI *disp, StepperMotor *stp, Input *ui,
                       long encoderLimitMin, long encoderLimitMax) {
        display = disp;
        stepper = stp;
        userInput = ui;
        limitMin = encoderLimitMin;
        limitMax = encoderLimitMax;

        encoderCountFiltered = getCount();
    }
};

#endif