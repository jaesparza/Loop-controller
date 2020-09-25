# Loop antenna tunning control [![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html) ![CI](https://github.com/jaesparza/Loop-controller/workflows/CI/badge.svg?branch=master)<br>

This project implements a tunning control system for magnetic loop antennas. The antenna is tunned by turning a variable capacitor through a stepper motor at reduced speeds. The controller generates the step signals to be provided to the driver, allows movement only within the specified limits and handles the user interface.

Main characteristics:
- Configurable speeds for fast and slow operation.
- Support for stepper motors of different pulses per rotation and with planetary reductions.
- Smooth stepper motor rotation through microstepping.
- Movement limitation based on discrete step counts or on encoder readings via ADC.

This repository hosts:
- Design calculations
- Hardware designs: schematic, PCB layouts and Gerbers ready to upload for production
- Software implementation of a reconfigurable controller to operate vacuum and butterfly capacitors, with different rotation limit control strategies.
- Notes on mechanical aspects and component selection.

The repository hosts two prototypes: a wired and a wireless control system. As of today only the wired system is complete.

## Wired control - Completed and deployed

| [Software](https://github.com/jaesparza/Loop-controller/tree/master/Software/tunerControllerGen1) | 
[Hardware](https://github.com/jaesparza/Loop-controller/tree/master/pcb/initialPrototype) |

This is a working system relying on a wired connection to deliver motor coil currents as well as reading back the encoder position.

The user interface is implemented through:
- a 16x2 LCD screen to display current capacitor position with a bar and a count,
- two push buttons to trigger clockwise or counter-clockwise rotations,
- a switch to select fast or slow speed.

In my implementation I use an ethernet network cable to be run in parallel with the coaxial cable carrying the RF singal. I have not experienced problems with electrical noise or spurious readings in the ADC due to long cable runs.


 ## Wireless control - Prototype, on hold
Currently under development, this second version of the controller features wireless control over 802.15.4. The remote control board is intended to be placed together with the antenna in the remote location. The user interacts with the control through a PC application.