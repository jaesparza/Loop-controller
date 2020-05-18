#ifndef _MODE_OPERATE_H
#define _MODE_OPERATE_H

#include "Mode.h"

class ModeOperate : public Mode {
  private:
    uint8_t updatePending = false;
    uint8_t operateMotor(int speed, uint8_t CW, uint8_t CCW) {

        uint8_t motorMoved = false;
        stepper->setSpeed(speed);

        if (CW) {
            if (stepper->getRotationCount() > SOFT_LIMIT_MIN) {
                stepper->enableMotor();
                stepper->rotateCW();
                motorMoved = true;
            }
        } else if (CCW) {
            if (stepper->getRotationCount() < SOFT_LIMIT_MAX) {
                stepper->enableMotor();
                stepper->rotateCCW();
                motorMoved = true;
            }
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
    virtual void execute() {
        // display->showText(MODE_OPERATION_MESSAGE);

        uint8_t moved = false;

        userInput->readInputs();
        display->update(stepper->getRotationCount());

        moved = operateMotor(userInput->getSpeed(), userInput->isRotateCW(),
                             userInput->isRotateCCW());

        if (moved) {
            display->updateRefreshCount();
            updatePending = true;
            // The motor has just moved, so do not update EEPROM position again
            // since most likely it will move again in the coming iteration.
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