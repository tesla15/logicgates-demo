#include "lib.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);  

void bootloader() {
  lcd.clear();
  printLCD(0,0,"01010101010101010101");
  printLCD(0,1,"10101010101010101010");
  printLCD(0,2,"01010101010101010101");
  printLCD(0,3,"10101010101010101010");
  delay(30);
  lcd.clear();
  printLCD(0,1,"01010101010101010101");
  printLCD(0,0,"10101010101010101010");
  printLCD(0,3,"01010101010101010101");
  printLCD(0,2,"10101010101010101010");
  delay(30);
  lcd.clear();
  printLCD(0,0,"01010101010101010101");
  printLCD(0,1,"10101010101010101010");
  printLCD(0,2,"01010101010101010101");
  printLCD(0,3,"10101010101010101010");
  delay(30);
  lcd.clear();
  printLCD(0,1,"01010101010101010101");
  printLCD(0,0,"10101010101010101010");
  printLCD(0,3,"01010101010101010101");
  printLCD(0,2,"10101010101010101010");
  delay(30);
  lcd.clear();
  printLCD(6,1,"made by");
  printLCD(4,2,"Maciek Godek");
  delay(2000);
  lcd.clear();
}

void initGlobal() {
  Serial.begin(115200);
  pinMode(D7, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  pinMode(16, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D9, OUTPUT);
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

