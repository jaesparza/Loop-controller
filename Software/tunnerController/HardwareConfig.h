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

// Stepper driver signals
#define STEP_PIN   9
#define ENABLE_PIN 8
#define DIRECTION_PIN A1

#define MAX_COUNT 15810
#define COLUMN 16
#define COUNT_PER_COL (MAX_COUNT/COLUMN)

#endif /* HARDWARECONFIG_H_ */
