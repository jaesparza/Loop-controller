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
        }

        delay(OPERATION_DELAY);
    }

  public:
    virtual void execute() {
        // display->showMode(MODE_OPERATION_MESSAGE);
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