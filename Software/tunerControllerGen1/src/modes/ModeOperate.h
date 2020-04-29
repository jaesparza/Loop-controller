#ifndef _MODE_OPERATE_H
#define _MODE_OPERATE_H

#include "Mode.h"

class ModeOperate : public Mode {
  private:
    void operateMotor() {

        stepper->setSpeed(userInput->getSpeed());

        if (userInput->isRotateCW()) {
            stepper->enableMotor();
            stepper->rotateCW();
            display->updateRefreshCount();
        } else if (userInput->isRotateCCW()) {
            stepper->enableMotor();
            stepper->rotateCCW();
            display->updateRefreshCount();
        } else {
            stepper->disableMotor();
            display->updateImmediate();
            //@ TODO here we could also update the count
        }

        if (userInput->getSpeed() == SLOW) {
            delay(OPERATION_DELAY_SLOW);
        } else {
            delay(OPERATION_DELAY_FAST);
        }
    }

  public:
    virtual void execute() {
        // display->showText(MODE_OPERATION_MESSAGE);
        userInput->readInputs();
        display->update(stepper->getRotationCount());
        operateMotor();
    }

    ModeOperate(UI *disp, StepperMotor *stp, Input *ui) {
        display = disp;
        stepper = stp;
        userInput = ui;
    }
};

#endif // _MODE_OPERATE_H