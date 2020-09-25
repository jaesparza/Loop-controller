/*
 * Filename:     tunerControlGen1.ino
 * Description:  main file for the tunner control unit.
 * Author: jaesparza - jaesparza@gmail.com
 *
 * Compiled with arduino IDE version 1.8.10, edited with VScode and formatted
 * with with clang-format.
 *
 * Project: Loop atenna control - Gen 1
 * Hardware schematics: See HW folder in Github
 *
 * WARGING: High voltages and lethal currents can develop in an efficient loop
 * antenna. If not properly constructed, lethal voltages could be derived to
 * your control board. Us it at your OWN risk.
 *
 * Pending improvements:
 *  - Write the calibration mode
 *  - Add soft limits
 */

// Include hardware control classes
#include "./src/hwControl/EepromAccess.h"
#include "./src/hwControl/Input.h"
#include "./src/hwControl/StepperMotor.h"
#include "./src/hwControl/UI.h"

// Include operational logic classes
#include "./src//modes/ModeOperateEncoder.h"
#include "./src/modes/Mode.h"
#include "./src/modes/ModeCalibrate.h"
#include "./src/modes/ModeOperate.h"

// Initialize the pointers before getting the instances
Input *Input::instance = 0;
UI *UI::instance = 0;
StepperMotor *StepperMotor::instance = 0;
EepromAccess *EepromAccess::instance = 0;

// Global HAL declarations
Input *userInput = 0;
UI *display = 0;
StepperMotor *stepper = 0;
EepromAccess *eeprom = 0;

// Global operational mode declaration
Mode *currentMode = 0;

// Setup code, run once
void setup() {
    userInput = Input::getInstance();
    display = UI::getInstance();
    stepper = StepperMotor::getInstance();
    eeprom = EepromAccess::getInstance();

    // Initialize hardware
    userInput->initInput();
    stepper->initMotorState();
    display->initLCD();

    // Initialize UI
    display->makeEmptyBar();
    display->showText(LINE_1_COUNT);

    // Check inputs and enter configuration configuration mode if requested
    userInput->readInputs();

    if (userInput->CwAndCCWPushed()) {
        eeprom->storePosition(0);
    }

    // Recover last position from memory
    stepper->setRotationCount(eeprom->getPosition());
    if (userInput->CwAndCCWPushed()) {
        currentMode = new ModeCalibrate(display, stepper, userInput, eeprom);
    } else {
#if defined(CONF_1) || defined(CONF_2)
        currentMode = new ModeOperate(display, stepper, userInput, eeprom,
                                      SOFT_LIMIT_MIN, SOFT_LIMIT_MAX);
#elif defined(CONF_3)
        currentMode = new ModeOperateEncoder(display, stepper, userInput,
                                             ENCODER_MIN, ENCODER_MAX);
#else
#error "No active configuration"
#endif
    }
}

// Continuous execution of the selected mode
void loop() {
    currentMode->execute();
}