
#ifndef HARDWARE_CONFIGURATION_H
#define HARDWARE_CONFIGURATION_H

#define DEBUG_1 3
#define DEBUG_2 8
#define DEBUG_3 12

#define SERIAL Serial1

// Hardware connections
// Connection to the motor driver
#define ENABLE_PIN    5
#define STEP_PIN      6
#define DIRECTION_PIN 7

// Microstep connection to the controller
#define MS1_PIN       9     
#define MS2_PIN       4
#define MS3_PIN       2

// XBEE sleep pin
#define SLEEP_PIN     10

// On board RX led pin
#define RXLED         17

#endif // HARDWARE_CONFIGURATION_H