#include "StepperMotor.h"
#include <Arduino.h>

void StepperMotor::initMotorState() {
    disableMotor();
    // digitalWrite(DIRECTION_PIN, HIGH);
}

int StepperMotor::getRotationCount() {
    return rotationCount;
}

void StepperMotor::setSpeed(int speed) {
    if (speed == SLOW) {
        activeDuration = durationSlow;
    } else {
        activeDuration = durationFast;
    }
}

void StepperMotor::rotateCW() {
    digitalWrite(DIRECTION_PIN, HIGH);
    rotationCount--;
    sendPulse();
}

void StepperMotor::rotateCCW() {
    digitalWrite(DIRECTION_PIN, LOW);
    rotationCount++;
    sendPulse();
}

void StepperMotor::enableMotor() {
    digitalWrite(ENABLE_PIN, MOTOR_ENABLE);
}

void StepperMotor::disableMotor() {
    digitalWrite(ENABLE_PIN, MOTOR_DISABLE);
}

void StepperMotor::sendPulse() {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(activeDuration);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(activeDuration);
}

StepperMotor *StepperMotor::getInstance() {
    if (!instance) {
        instance = new StepperMotor();
    }
    return instance;
}

void StepperMotor::setRotationCount(int rotCount) {
    rotationCount = rotCount;
}

StepperMotor::StepperMotor() {}