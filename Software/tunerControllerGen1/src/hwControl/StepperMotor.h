#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include "../../HardwareConfig.h"

#define MOTOR_ENABLE  0
#define MOTOR_DISABLE 1

#define SLOW 1
#define FAST 0

class StepperMotor {
  public:
    void initMotorState();
    void rotateCW();
    void rotateCCW();
    void setSpeed(int speed);
    void enableMotor();
    void disableMotor();

    int getRotationCount();
    static StepperMotor *getInstance();

  private:
    int rotationCount = 0;
    int orientation = 0;
    int speed = 0;

    int activeDuration = DELAY_SLOW;
    int const durationSlow = DELAY_SLOW;
    int const durationFast = DELAY_FAST;

    static StepperMotor *instance;
    StepperMotor();

    void sendPulse();
};

#endif // STEPPER_MOTOR_H