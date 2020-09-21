

#ifndef ENCODER_H
#define ENCODER_H

#include "../../HardwareConfig.h"
#include <Arduino.h>

/*
 Will read the position of the potentiometer and translate it into a capacitor
 absolute position.
 - Where are the limits stored - Max/min position?
 -

*/

class Encoder {
  public:
    int getPosition() {}

  private:
    int getCount() {
        return analogRead(ENCODER);
    }
}

#endif