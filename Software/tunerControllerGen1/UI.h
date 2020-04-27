/*
*  Filename: UI.h 
*  Description:
*  
*  Custom character creator: https://www.quinapalus.com/hd44780udg.html
*
*  Project: 
*  Author: jaesparza - jaesparza@gmail.com
*/

#ifndef UI_H_
#define UI_H_

#include <Arduino.h>
#include "HardwareConfig.h"
#include "characterDefinitions.h"

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

class UI {
    public:
        void updateBar(int position);
        void initLCD();
        void makeFullBar();
        void makeEmptyBar();
        void makeEmptyBar(int start, int last);
        void clearLCDLine(int line);
        void updateCount(int rotationCount);
        void showText();
        void writeNumber(char n);
        void removeNullTermination(char * buffer,int len);
        void progressBarTest();
        void showNumber(int,int,int);
        void udpateDisplay();
        void updateRefreshCount();
        void update(int);
        
    private:
        long int lastRefresh = 0;
        long int refreshCount = 0;
};

#endif /* UI_H_ */
