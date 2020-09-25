# Hardware notes

Fixes:

* **Pull-up fix in the enable motor stepper controller signal**  it is important to add a 1 kOhm pull-up to the enable signal so it has a defined state when the microcontroller is going through a power-on/reset. It can be added easily on the back of the PCB between the *Enable* and the *Vcc* pins.


## Wired control board
- Only revB of the PCB is available in here, revA had routing problems and was discarded in the design tool.
- The hardware was developed with easyEDA and I used JLPCB for production.

## Wireless control board
- The hardware was developed with KiCAD and I used JLPCB for production.

Misc. notes:
- Power through LiPo battery - solar panel could be used.
- The control board runs at 3V to reduce power consumption and to avoid level shifters to interface peripherals. Software is currently under development. 

