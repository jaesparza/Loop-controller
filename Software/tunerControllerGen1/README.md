# Tunner controller - Generation 1
This is the firmare for the first generation control board. It has been developed using CPP and parts of the Arduino framework as Hardware Abstraction Layer (HAL). 

Main features are:
* The firmware can be configured to control different kinds stepper motors at different speeds.
* The LCD position bar can be recalibrated to represent approximate capacitance graphically between min and max values.
* The LCD refresh rate can be reconfigured so it does not affect motor operation.
* EEPROM Storage of last position
* Easily portable to other architectures by changing the hw dependand class implementations (`Input.cpp`, `StepperMotor.cpp` and `UI.cpp`).

Features to be implemented:
* Softlimits to stop rotation movement if going below MIN or beyond MAX positions.

## Software structure
The control software is structured as depicted below. Comments after `##`

```bash
tunerControlGen1/
|── tunnerControllerGen1.ino                ## Initialization and entry point
├── HardwareConfig.h                        ## Configuration of hardware connections and motor timing
├── src/                                    
│   ├── lib                                 ## Thir party library for faster LCD interfacing (no blocking)
|   |   ├── LiquidCrystalFast.h
|   |   └── LiquidCrystalFast.cpp
│   ├── modes                               ## Operational modes
|   |   ├── Mode.h
|   |   ├── ModeCalibrate.h
|   |   └── ModeOperate.h
│   ├── hwControl                           ## Hardware dependant class definitions and implementations for Arduino
|   |   ├── characterDefinitions.h
|   |   ├── UI.h
|   |   ├── UI.cpp
|   |   ├── StepperMotor.h
|   |   ├── StepperMotor.cpp
|   |   ├── Input.h
|   |   └── Input.cpp
|   └── 
└── 
```

## Description

## How to configure the firmware

Insert table with parameter description

```C
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
#define REFRESH_INTERVAL     50
#define DELAY_SLOW           300
#define DELAY_FAST           100
#define MAX_COUNT            1600
#define OPERATION_DELAY_SLOW 50
#define OPERATION_DELAY_FAST 10
#endif // CONF_1
```
