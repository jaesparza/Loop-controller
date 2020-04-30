
#include "UI.h"

LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);

void clearLCDLine(int line)
{               
        lcd.setCursor(0,line);
        for(int n = 0; n < 16; n++) 
        {
                lcd.print(" ");
        }
}

void makeFullBar(){
  lcd.setCursor(0,0);
  lcd.write(LEFT_DELIMITER);

  for(int i=1;i<15;i++) {
    lcd.setCursor(i,0);
    lcd.write(POSITION_BAR);
  }

  lcd.setCursor(15,0);
  lcd.write(RIGHT_DELIMITER);
}

void makeEmptyBar(int start, int last) {
  lcd.setCursor(0,0);
  lcd.write(LEFT_DELIMITER);

  for(int i = start;i<last;i++) {
    lcd.setCursor(i,0);
    lcd.write(EMPTY_CHARACTER);
  }

  lcd.setCursor(15,0);
  lcd.write(EMPTY_RIGHT);
}

void initLCD() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.createChar(SOLID_BLOCK, solidBlock);
  lcd.createChar(LEFT_DELIMITER, leftDelimiterThin);
  lcd.createChar(RIGHT_DELIMITER, rightDelimiterThin);
  lcd.createChar(POSITION_BAR, positionBarThin);
  lcd.createChar(EMPTY_LEFT, emptyLeftThin);
  lcd.createChar(EMPTY_RIGHT, emptyRightThin);
  lcd.createChar(EMPTY_CHARACTER, emptyCharacterThin);
}

void updateScreen(int position) {
  // Max position is 0 - 15
  //lcd.clear();
  if (position == 0){
    makeEmptyBar(1,16);
  }
  if ((position > 0 ) && (position < 15)) {
    lcd.setCursor(0,0);
    lcd.write(LEFT_DELIMITER);
    for(int i=1;i<position+1;i++) {
      lcd.setCursor(i,0);
      lcd.write(POSITION_BAR);
    }
    for(int j=position+1;j<15;j++) {
      lcd.setCursor(j,0);
      lcd.write(EMPTY_CHARACTER);
    }
      lcd.setCursor(15,0);
      lcd.write(EMPTY_RIGHT);
  }
  if (position == 15) {
    makeFullBar();
  }
}

void showText() {
    lcd.setCursor(0,1);
    lcd.print(LINE_1_COUNT);
} 

/*
void updateCount(int rotationCount) {
    showText();
    lcd.setCursor(LINE_1_COUNT_LEN, 1);
    lcd.setCursor(0,1);
    String position = String(rotationCount);
    position = String(LINE_1_COUNT + position);
    lcd.print(position);
}*/


void updateCount(int rotationCount) {
    showText();

    lcd.setCursor(LINE_1_COUNT_LEN, 1);
    // Convert rotationCount to char array
    // Check length
    // Start at the end of the display, position 15
    char buffer[7] = {' ',' ',' ',' ',' ',' ',' '};
    
    itoa(rotationCount, buffer, 10);

    removeNullTermination(buffer,7);

    lcd.setCursor(10,1);
    lcd.write(buffer[0]); // Sign

    lcd.setCursor(11,1);
    lcd.write(buffer[1]); 
    lcd.setCursor(12,1);
    lcd.write(buffer[2]);
    lcd.setCursor(13,1);
    lcd.write(buffer[3]);  
    lcd.setCursor(14,1);
    lcd.write(buffer[4]);  
    lcd.setCursor(15,1);
    lcd.write(buffer[5]);  
}

void removeNullTermination(char * buffer,int len) {
    for(int n= 0; n< len; n++) {
        if (buffer[n] == '\0') {
            buffer[n] = ' ';
        }
    }    
}



void showNumber(int number, int row, int column) {
    
}