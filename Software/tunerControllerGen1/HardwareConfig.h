/*
 *  Filename: HardwareConfig.h
 *
 * Description:
 *  - Contains the hardware specific configurations
 *  - Defines timing delays for stepper motor control
 *
 * This software can be reused with other hardware configuration by only
 * changing the signal mapping.
 *
 * WARGING: High voltages and lethal currents can develop in an efficient loop
 * antenna. If not properly constructed, lethal voltages could be derived to
 * your control board. Us it at your OWN risk.
 *
 * Last update: see GIT log
 *
 * Author: jaesparza - jaesparza@gmail.com
 */

#ifndef HARDWARECONFIG_H_
#define HARDWARECONFIG_H_

/////////// REMAP AT YOUR OWN RISK   ///////////////////////////////

// User Input/Output signals
#define CCW_IN      13
#define CW_IN       12
#define SPEED       11
#define BUTTON_1_IN A3

#define PROFILE_PIN A2

// Potentiometer connected to ADC channel 0
#define ENCODER A0

// Stepper driver signals
#define STEP_PIN      9
#define ENABLE_PIN    8
#define DIRECTION_PIN A1

// LCD signals
#define RS     3
#define ENABLE 2
#define D4     7
#define D5     6
#define D6     5
#define D7     4
/////////////////////////////////////////////////////////////////////

// LCD interface definitions
#define COLUMNS       16
#define ROWS          2
#define COUNT_PER_COL (MAX_COUNT / COLUMNS)

// Select the configuration to be used
#define CONF_3

#ifdef CONF_1
/* Configuration for a stepper motor of 400 pulses per revolution, no planetary
 * reduction built-in.
 *
 *  This motor is intented to be used with a butterfly capacitor. This capacitor
 * type goes from minimum capacity to maximum with a 90 deg rotation = 1/4 of a
 * full rotation. Coupling to the capacitor is directly to the shaft (no
 * additional mechanical reduction).
 *
 *  Microswitches configured for maximum microstepping for minimum vibrations.
 *  switches 1 - LOW
 *           2 - LOW
 *           3 - LOW
 */
#define REFRESH_INTERVAL     50
#define DELAY_SLOW           300
#define DELAY_FAST           100
#define MAX_COUNT            1600
#define DECIMATE             1
#define OPERATION_DELAY_SLOW 50
#define OPERATION_DELAY_FAST 10
#define SOFT_LIMIT_MIN       0
#define SOFT_LIMIT_MAX       1600

// If defined the motor control operation algorithm will not check for limits
//#define DISABLE_SOFT_LIMITS
#endif // CONF_1

#ifdef CONF_2
/* Configuration for a stepper motor 200 pulses per revolution and
 *  a planetary gear reduction of 1:5
 *
 *  This motor is intented to be used with a vacuum capacitor of 16 turns and
 * coupled directly to the capacitor shaft (no additional mechanical reduction).
 *
 *  Microswitches configured for maximum microstepping for minimum vibrations.
 *  switches 1 - LOW
 *           2 - LOW
 *           3 - LOW
 */
#define REFRESH_INTERVAL     3000
#define DELAY_SLOW           300
#define DELAY_FAST           150
#define MAX_COUNT            15900
#define DECIMATE             10
#define OPERATION_DELAY_SLOW 0
#define OPERATION_DELAY_FAST 0
#define SOFT_LIMIT_MIN       0
#warning "Soft limit max remains to be checked"
#define SOFT_LIMIT_MAX 15900000

#endif

#ifdef CONF_3
/* If new configuration is created, document it.
 * Replace the #error macros with the relevant figures.
 * Configuration for a stepper motor ...
 *
 *  This motor is intented to be used with ...
 *
 *  Microswitches configured ...
 *  switches 1 - LOW/HIGH
 *           2 - LOW/HIGH
 *           3 - LOW/HIGH
 */

#define REFRESH_INTERVAL     3000
#define DELAY_SLOW           300
#define DELAY_FAST           150
#define MAX_COUNT            15900
#define DECIMATE             1
#define OPERATION_DELAY_SLOW 0
#define OPERATION_DELAY_FAST 0

#define SOFT_LIMIT_MIN 0
#define SOFT_LIMIT_MAX 15900000

#define ENCODER_MIN 378
#define ENCODER_MAX 1023

#endif

#endif /* HARDWARECONFIG_H_ */
