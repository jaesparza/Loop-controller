#ifndef _MODE_CALIBRATE_H
#define _MODE_CALIBRATE_H

#include "Mode.h"

class ModeCalibrate : public Mode {
  private:
    void calibration() {
        // waitForRelease();
        userInput->readInputs();

        if (userInput->getExtraPB() == false) {
            display->showMode(CALIBRATION_COMPLETED);
        }
    }

    //@TODO: Store max count here has to be implemented so it writes to EEPROM
    bool storeMaxCount(int maxCount) {
        return true;
    }

  public:
    virtual void execute() {
        display->showMode(MODE_CALIBRATION_MESSAGE);
        calibration();
    }

    ModeCalibrate(UI *disp, StepperMotor *stp, Input *ui) {
        display = disp;
        stepper = stp;
        userInput = ui;
    }
};

#endif // _MODE_CALIBRATE