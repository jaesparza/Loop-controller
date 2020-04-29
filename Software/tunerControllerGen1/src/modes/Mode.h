#ifndef _MODE_H
#define _MODE_H

#include "../hwControl/Input.h"
#include "../hwControl/StepperMotor.h"
#include "../hwControl/UI.h"

class Mode {
  private:
  protected:
    UI *display = 0;
    StepperMotor *stepper = 0;
    Input *userInput = 0;

  public:
    virtual void execute() = 0;
};

#endif // _MODE_H