#include "lib.h"
#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void initLCD() {
  lcd.init();
  lcd.backlight();
}

void printLCD(int columnlcd, int rowlcd, String textlcd) {
  lcd.setCursor(columnlcd, rowlcd);
  lcd.print(textlcd);
}

