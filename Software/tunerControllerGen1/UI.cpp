#include "UI.h"

#if defined(USE_FAST_LIB)
LiquidCrystalFast lcd(RS, ENABLE, D4, D5, D6, D7);
#else
LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);
#endif

void UI::clearLCDLine(int line) {
    lcd.setCursor(0, line);
    for (int n = 0; n < 16; n++) {
        lcd.print(" ");
    }
}

void UI::makeFullBar() {
    lcd.setCursor(0, 0);
    lcd.write(LEFT_DELIMITER);

    for (int i = 1; i < 15; i++) {
        lcd.setCursor(i, 0);
        lcd.write(POSITION_BAR);
    }

    lcd.setCursor(15, 0);
    lcd.write(RIGHT_DELIMITER);
}

void UI::makeEmptyBar() {
    makeEmptyBar(1, 16);
}

void UI::makeEmptyBar(int start, int last) {
    lcd.setCursor(0, 0);
    lcd.write(LEFT_DELIMITER);

    for (int i = start; i < last; i++) {
        lcd.setCursor(i, 0);
        lcd.write(EMPTY_CHARACTER);
    }

    lcd.setCursor(15, 0);
    lcd.write(EMPTY_RIGHT);
}

void UI::initLCD() {
    // Sets up the LCD's number of columns and rows
    lcd.begin(COLUMNS, ROWS);
    // Loads the custom characters in the predefined positions
    lcd.createChar(SOLID_BLOCK, solidBlock);
    lcd.createChar(LEFT_DELIMITER, leftDelimiterThin);
    lcd.createChar(RIGHT_DELIMITER, rightDelimiterThin);
    lcd.createChar(POSITION_BAR, positionBarThin);
    lcd.createChar(EMPTY_LEFT, emptyLeftThin);
    lcd.createChar(EMPTY_RIGHT, emptyRightThin);
    lcd.createChar(EMPTY_CHARACTER, emptyCharacterThin);
}

void UI::updateBar(int position) {
    // Max position is 0 - 15
    // lcd.clear();
    if (position == 0) {
        makeEmptyBar(1, 16);
    }
    if ((position > 0) && (position < 15)) {
        lcd.setCursor(0, 0);
        lcd.write(LEFT_DELIMITER);
        for (int i = 1; i < position + 1; i++) {
            lcd.setCursor(i, 0);
            lcd.write(POSITION_BAR);
        }
        for (int j = position + 1; j < 15; j++) {
            lcd.setCursor(j, 0);
            lcd.write(EMPTY_CHARACTER);
        }
        lcd.setCursor(15, 0);
        lcd.write(EMPTY_RIGHT);
    }
    if (position == 15) {
        makeFullBar();
    }
}

void UI::showText(String mode) {
    lcd.setCursor(0, 1);
    lcd.print(mode);
}

void UI::updateCount(int rotationCount) {
    showText(LINE_1_COUNT);
    lcd.setCursor(LINE_1_COUNT_LEN, 1);

    // Convert rotationCount to char array
    // Remove null termination
    // Start at the end of the display, position 15
    // Print the numbers
    char buffer[7] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};

    itoa(rotationCount, buffer, 10);
    removeNullTermination(buffer, 7);

    lcd.setCursor(10, 1);
    lcd.write(buffer[0]); // Sign

    lcd.setCursor(11, 1);
    lcd.write(buffer[1]);
    lcd.setCursor(12, 1);
    lcd.write(buffer[2]);
    lcd.setCursor(13, 1);
    lcd.write(buffer[3]);
    lcd.setCursor(14, 1);
    lcd.write(buffer[4]);
    lcd.setCursor(15, 1);
    lcd.write(buffer[5]);
}

void UI::update(int rotationCount) {
    if ((refreshCount - lastRefresh) > 500) {
        // digitalWrite(PROFILE_PIN,HIGH);
        // Performing this update takes around 10 ms with both fastlib also with
        // arduino built-in LiquidCrystal library - Mileage may vary depending
        // on the LCD display controller
        //
        // Uncomment the surrounding profiling pin statements, make sure they
        // are not toggled anywhere else and masure to check for your specific
        // LCD
        updateCount(rotationCount);
        updateBar((rotationCount) / COUNT_PER_COL);
        // digitalWrite(PROFILE_PIN,LOW);

        lastRefresh = refreshCount;
    }
}

void UI::updateRefreshCount() {
    refreshCount++;
}

void UI::removeNullTermination(char *buffer, int len) {
    for (int n = 0; n < len; n++) {
        if (buffer[n] == '\0') {
            buffer[n] = ' ';
        }
    }
}

void UI::showNumber(int number, int row, int column) {}

// Some demo code to test the progress bar, will remove and add solid blocks
void UI::progressBarTest() {
    for (int i = 0; i < 16; i++) {
        updateBar(i);
        delay(50);
    }

    for (int i = 15; i >= 0; i--) {
        updateBar(i);
        delay(50);
    }
}

UI *UI::getInstance() {
    if (!instance) {
        instance = new UI();
    }
    return instance;
}

UI::UI() {}