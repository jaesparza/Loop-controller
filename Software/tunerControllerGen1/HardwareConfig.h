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

#define CONF_1

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
#define DELAY_SLOW      1000
#define DELAY_FAST      600
#define MAX_COUNT       800
#define OPERATION_DELAY 10
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
#define DELAY_SLOW      300
#define DELAY_FAST      150
#define MAX_COUNT       18036
#define OPERATION_DELAY 0
#endif // CONF_2

/* If new configuration is created, document it.
 * Configuration for a stepper motor ...
 *
 *  This motor is intented to be used with ...
 *
 *  Microswitches configured ...
 *  switches 1 - LOW/HIGH
 *           2 - LOW/HIGH
 *           3 - LOW/HIGH
 */
#ifdef CONF_3
#define DELAY_SLOW      XXX
#define DELAY_FAST      XXX
#define MAX_COUNT       XXX
#define OPERATION_DELAY XXX
#endif

#endif /* HARDWARECONFIG_H_ */
