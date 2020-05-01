# Loop antenna tunning control [![License: GPL v2](https://img.shields.io/badge/License-GPL%20v2-blue.svg)](https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html) ![CI](https://github.com/jaesparza/Loop-controller/workflows/CI/badge.svg?branch=master)<br>
This project implements a tunning control for a magnetic loop antenna. The antenna is tunned by turning a variable capacitor through a stepper motor. The controller is responsible for turning the stepper motor axis based on user input.

## v2 - wireless control
Currently under development, this second version of the controller features wireless control over 802.15.4. The remote control board is intended to be placed together with the antenna in the remote location. For powering the board there are two options:
- Power through BIAS-T, injecting power into the coaxial line carrying the rf signal.
- Power through LiPo battery.

The control board runs at 3V to reduce power consumption and to avoid level shifters to interface peripherals. Software is currently under development. 

Other remarks:
- The hardware is developed with KiCAD.
- I am using JLPCB for production. Order your own by sending the gerbers.

## v1 - initial prototype
This was the initial implementation of the controller. The board integrates a 16x2 LCD screen and push buttons to control the stepper motor. The motor coil signals are sent over a network cable, to be run in parallel with the coaxial cable to the antenna.

Other remarks:
 - Only revB of the PCB is available in here, since revA had routing problems.
 - The hardware was developed with easyEDA.
 - I used JLPCB for production. Order your own by sending the gerbers.