#include "StepperMotor.h"

void StepperMotor::initMotorState() {
    digitalWrite(DIRECTION_PIN, HIGH);
    disableMotor();
}

long int StepperMotor::getRotationCount() {
    return rotationCount;
}

void StepperMotor::setSpeed(int speed) {
    if (speed == SLOW) {
        activeDuration = durationSlow;
    } else {
        activeDuration = durationFast;
    }
}

void StepperMotor::setSlow() {
    activeDuration = DELAY_SLOW;
}

void StepperMotor::setFast() {
    activeDuration = DELAY_FAST;
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