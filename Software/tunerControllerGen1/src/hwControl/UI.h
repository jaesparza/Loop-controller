/*
 * Filename: UI.h
 * Description: Class to handle a 16X2 LCD screen to display position
 * information to the user.
 *
 * Author: jaesparza - jaesparza@gmail.com
 */

/* @TODO
boolean waitForRelease(){
  extraPB = digitalRead(BUTTON_1_IN);
  while(extraPB == LOW) {
      extraPB = digitalRead(BUTTON_1_IN);
  }
  return true;
}*/

#ifndef UI_H
#define UI_H

#define USE_FAST_LIB
#if defined(USE_FAST_LIB)
#include "../lib/LiquidCrystalFast.h"
#else
#include <LiquidCrystal.h>
#endif

#define INIT_MESSAGE     "   Loop tunner"
#define CONFIG_MESSAGE   "CFG mode - LOW"
#define LINE_1_COUNT     "Position: "
#define LINE_1_COUNT_LEN 10

#define MODE_CALIBRATION_MESSAGE "Calibration"
#define MODE_OPERATION_MESSAGE   "Operation"
#define CALIBRATION_COMPLETED    "Calibration done"

class UI {
  public:
    void updateBar(int position);
    void initLCD();
    void makeFullBar();
    void makeEmptyBar();
    void makeEmptyBar(int start, int last);
    void clearLCDLine(int line);
    void updateCount(int rotationCount);
    void writeNumber(char n);
    void removeNullTermination(char *buffer, int len);
    void progressBarTest();
    void showNumber(int, int, int);
    void udpateDisplay();
    void updateRefreshCount();
    static UI *getInstance();
    void showText(String);
    void updateImmediate();
    void update(int);

  private:
    int lastRefresh = 0;
    int refreshCount = 0;
    uint8_t requestUpdate = false;

    static UI *instance;
    UI();

    void clearUpdateImmediate();
};

#endif /* UI_H_ */
