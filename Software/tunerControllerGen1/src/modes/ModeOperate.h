#ifndef _MODE_OPERATE_H
#define _MODE_OPERATE_H

#include "Mode.h"

class ModeOperate : public Mode {
  private:
    uint8_t updatePending = false;

    bool checkLimits() {
        if (userInput->isRotateCW()) {
            return ((stepper->getRotationCount()) > SOFT_LIMIT_MIN ? true
                                                                   : false);

        } else if (userInput->isRotateCCW()) {
            return ((stepper->getRotationCount()) < SOFT_LIMIT_MAX ? true
                                                                   : false);
        }
    }

  public:
    virtual void execute() {
        // display->showText(MODE_OPERATION_MESSAGE);

        uint8_t moved = false;

        userInput->readInputs();
        display->update(stepper->getRotationCount());

        if (checkLimits()) {
            moved = operateMotor(userInput->getSpeed(), userInput->isRotateCW(),
                                 userInput->isRotateCCW());
        } else {
            stepper->disableMotor();
        }

        if (moved) {
            display->updateRefreshCount();
            updatePending = true;
            // The motor has just moved, so do not update EEPROM position
            // again since most likely it will move again in the coming
            // iteration.
        } else {
            display->updateImmediate();
            if (updatePending) { // Store now in EEPROM
                eeprom->storePosition(stepper->getRotationCount());
                updatePending = false;
            }
        }
    }

    ModeOperate(UI *disp, StepperMotor *stp, Input *ui, EepromAccess *epr) {
        display = disp;
        stepper = stp;
        userInput = ui;
        eeprom = epr;
    }
};

#endif // _MODE_OPERATE_H