#ifndef EEPROM_ACCESS_H
#define EEPROM_ACCESS_H

#include "../../HardwareConfig.h"
#include "EEPROM.h"

class EepromAccess {

  private:
    static EepromAccess *instance;
    EepromAccess(){};

    int const address = 0;
    int addressPosition = 1; // Two bytes needed

  public:
    static EepromAccess *getInstance() {
        if (!instance) {
            instance = new EepromAccess();
        }
        return instance;
    }

    uint8_t storePosition(int position) { // Around 4 ms @ 26 Mhz
        EEPROM.write(1, (position & 0xFF00) >> 8);
        EEPROM.write(2, position & 0x00FF);
    }

    int getPosition() {
        uint8_t highByte = EEPROM.read(addressPosition);
        uint8_t lowByte = EEPROM.read(addressPosition + 1);
        return ((highByte << 8) | lowByte);
    }
};

#endif // EEPROM_ACCESS_H