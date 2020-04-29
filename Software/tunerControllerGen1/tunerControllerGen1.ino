/*
 * Filename:     tunnerControlGen1.ino
 * Description:  main file for the tunner control unit.
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
 * Author: jaesparza - jaesparza@gmail.com
 *
 * Pending improvements:
 *  - updateCount takes as parameter int however, the maximum number of counts
 *    is stored in a long, this has to be fixed
 *  - establish new, smooth control parameters for a 400 steps stepper motor
 *  - modify the code such that it stores position in eeprom
 */

#include "HardwareConfig.h"

#include "Input.h"
#include "StepperMotor.h"
#include "UI.h"

#include "Mode.h"
#include "ModeCalibrate.h"
#include "ModeOperate.h"

// Initialize the pointers before getting the instances
Input *Input::instance = 0;
UI *UI::instance = 0;
StepperMotor *StepperMotor::instance = 0;

// Global HAL declarations
Input *userInput = 0;
UI *display = 0;
StepperMotor *stepper = 0;

// Global operational mode declaration
Mode *currentMode = 0;

void setup() {

    userInput = Input::getInstance();
    display = UI::getInstance();
    stepper = StepperMotor::getInstance();

    // Initialize hardware
    display->initLCD();
    userInput->initInput();
    stepper->initMotorState();

    // Initialize UI
    display->makeEmptyBar();
    display->showText();

    // Check inputs and enter configuration configuration mode if requested
    userInput->readInputs();

    if (userInput->getExtraPB() == PUSHED) {
        currentMode = new ModeCalibrate(display, stepper, userInput);
    } else {
        currentMode = new ModeOperate(display, stepper, userInput);
    }
}

void loop() {
    currentMode->execute();
}