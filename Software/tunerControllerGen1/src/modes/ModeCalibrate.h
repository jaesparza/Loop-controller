#ifndef _MODE_CALIBRATE_H
#define _MODE_CALIBRATE_H

#include "Mode.h"

class ModeCalibrate : public Mode {
  private:
    //@TODO: Calibration routine has to be written
    void calibration() {
        display->showText(MODE_CALIBRATION_MESSAGE);
        // waitForRelease();
        userInput->readInputs();

        if (userInput->getExtraPB() == false) {
            display->showText(CALIBRATION_COMPLETED);
        }
    }

    void calibrationADC() {
        display->clearLCDLine(1);
        display->clearLCDLine(2);

        int val = analogRead(ENCODER);
        display->showText(String(val));
        delay(1000);
    }
    /////////////////////////////////////////////////////

    //@TODO: Store max count here has to be implemented so it writes to EEPROM
    bool storeMaxCount(int maxCount) {
        return true;
    }
    /////////////////////////////////////////////////////

  public:
    virtual void execute() {
        calibrationADC();
    }

    ModeCalibrate(UI *disp, StepperMotor *stp, Input *ui, EepromAccess *epr) {
        display = disp;
        stepper = stp;
        userInput = ui;
    }
};

#endif // _MODE_CALIBRATE