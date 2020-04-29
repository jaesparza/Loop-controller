#include "Input.h"

void Input::initInput() {
    pinMode(CW_IN, INPUT);
    pinMode(CCW_IN, INPUT);
    pinMode(SPEED, INPUT);
    pinMode(BUTTON_1_IN, INPUT);
    digitalWrite(BUTTON_1_IN, HIGH); // Enable the internal pull-ups
    pinMode(PROFILE_PIN, OUTPUT);

    pinMode(STEP_PIN, OUTPUT);
    pinMode(ENABLE_PIN, OUTPUT);
    pinMode(DIRECTION_PIN, OUTPUT);

    digitalWrite(PROFILE_PIN, LOW);
}

void Input::readInputs() {
    speedIn = digitalRead(SPEED);
    cwIn = digitalRead(CW_IN);
    ccwIn = digitalRead(CCW_IN);
    extraPB = digitalRead(BUTTON_1_IN);
}

int Input::getCcwIn() {
    return ccwIn;
}

int Input::getCwIn() {
    return cwIn;
}

int Input::getSpeed() {
    return speedIn;
}

int Input::getExtraPB() {
    return extraPB;
}

boolean Input::isRotateCCW() {
    if ((cwIn == RELEASED) && (ccwIn == PUSHED)) {
        return true;
    } else {
        return false;
    }
}

boolean Input::isRotateCW() {
    if ((cwIn == PUSHED) && (ccwIn == RELEASED)) {
        return true;
    } else {
        return false;
    }
}

Input *Input::getInstance() {
    if (!instance) {
        instance = new Input();
    }
    return instance;
}

Input::Input() {}