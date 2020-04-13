/*
 * HardwareConfig.h
 *
 *  Created on: 5 may. 2018
 *      Author: ja
 */

#ifndef HARDWARECONFIG_H_
#define HARDWARECONFIG_H_


// Input pins
#define CCW_IN 13
#define CW_IN 12
#define SPEED 11
#define BUTTON_1_IN A3

// LCD signals
#define RS		3
#define ENABLE	2
#define D4		7
#define D5		6
#define D6		5
#define D7		4

#define ROTATE_CW 1
#define ROTATE_CCW 2

#define CONF_1

#ifdef CONF_1
// Works well with a 400 steps/rev stepper motor
#define DELAY_SLOW 20
#define DELAY_FAST 10
#define MAX_COUNT 800 // Butterfly capacitor
// switches 1 - OFF
//          2 - OFF
//          3 - ON
#endif // CONF_1

#ifdef CONF_2
#define DELAY_SLOW 10
#define DELAY_FAST 1
#define MAX_COUNT 1600 
// switches 1 - OFF
//          2 - ON
//          3 - OFF
#endif // CONF_2

// Stepper driver signals
#define STEP_PIN   9
#define ENABLE_PIN 8
#define DIRECTION_PIN A1


#define COLUMN 16
#define COUNT_PER_COL (MAX_COUNT/COLUMN)

#endif /* HARDWARECONFIG_H_ */
