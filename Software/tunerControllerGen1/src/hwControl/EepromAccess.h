#ifndef EEPROM_ACCESS_H
#define EEPROM_ACCESS_H

#include "../../HardwareConfig.h"
#include "EEPROM.h"

class EepromAccess {

  private:
    static EepromAccess *instance;
    EepromAccess(){};

  public:
    static EepromAccess *getInstance() {
        if (!instance) {
            instance = new EepromAccess();
        }
        return instance;
    }

    uint8_t storePosition(int pos) {
        // Store position here
    }
};

#endif // EEPROM_ACCESS_H