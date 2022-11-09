#include "lib.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  

void bootloader() {
  lcd.clear();
  for (int i = 2; i > 0; i--) {
    printLCD(0, 0, "1010101010101010");
    printLCD(0, 1, "0101010101010101");
    delay(200);
    printLCD(0, 1, "1010101010101010");
    printLCD(0, 0, "0101010101010101");
    delay(200);
    lcd.clear();
    printLCD(4,0,"made by");
    printLCD(2,1,"Maciek Godek");
  }
  delay(1000);
  lcd.clear();
}

void initGlobal() {
  Serial.begin(115200);
  pinMode(D7, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
}

void initLCD() {
  lcd.init();
  lcd.backlight();
}

void printLCD(int columnlcd, int rowlcd, String textlcd) {
  lcd.setCursor(columnlcd, rowlcd);
  lcd.print(textlcd);
}

void clearLCD() {
  lcd.clear();
}

