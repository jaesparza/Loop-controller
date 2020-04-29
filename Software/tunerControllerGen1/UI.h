/*
 * Filename: UI.h
 * Description: Class to handle a 16X2 LCD screen to display position
 * information to the user.
 *
 * Author: jaesparza - jaesparza@gmail.com
 */

/* PENDING
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
#include "./src/lib/LiquidCrystalFast.h"
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
    void update(int);
    static UI *getInstance();
    void showText(String);

  private:
    long int lastRefresh = 0;
    long int refreshCount = 0;

    static UI *instance;
    UI();
};

#endif /* UI_H_ */
