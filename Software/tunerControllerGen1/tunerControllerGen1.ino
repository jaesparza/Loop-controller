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
 * antenna. If not properly constructed, lethal voltages could be present in
 * your control board. Us it at your OWN risk.
 *
 * Author: jaesparza - jaesparza@gmail.com
 *
 * Pending improvements:
 *  - updateCount takes as parameter int however, the maximum number of counts
 *    is stored in a long, this has to be fixed
 *  - create two strategies to control the motor: configuration and operation
 *  - establish new, smooth control parameters for a 400 steps stepper motor
 *  - modify the code such that it stores position in eeprom
 */

#include "HardwareConfig.h"
#include <Arduino.h>

#include "Input.h"
#include "StepperMotor.h"
#include "UI.h"

// Define different operational modes
#define BOOT_NORMAL_MODE false
#define BOOT_CONFIG_MODE true
boolean bootMode = BOOT_NORMAL_MODE;
boolean calibrationComplete = false;
// Strategy      * operationStrategy;

Input *Input::instance = 0;

Input *userInput;
UI *display;
StepperMotor *stepper;

void setup() {

    userInput = Input::getInstance();
    display = new UI();
    stepper = new StepperMotor();

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
        bootMode = BOOT_CONFIG_MODE;
        // operationStrategy = new Configuration();
    } else {
        bootMode = BOOT_NORMAL_MODE;
        // operationStrategy = new NormalOperation();
    }
}

bool storeMaxCount(int maxCount) {

    return true;
}

void loop() {

    // operationStrategy->run();

    if (bootMode == BOOT_CONFIG_MODE) {
        while (1) {
            configuration();
        }    // No need to re-evaluate bootMode
    } else { // BOOT_NORMAL_MODE
        while (1) {
            normalOperation();
        } // No need to re-evaluate bootMode, will iterate here
    }
}

void configuration() {
    // waitForRelease();
    userInput->readInputs();

    if (userInput->getExtraPB() == false) {
        storeMaxCount(10);
    }
}

void normalOperation() {
    userInput->readInputs();
    display->update(stepper->getRotationCount());
    operateMotor();
}

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