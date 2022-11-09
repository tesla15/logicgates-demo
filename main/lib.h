#ifndef LIB_H
#define LIB_H
#include <Arduino.h>

void initLCD();
void printLCD(int columnlcd, int rowlcd, String textlcd);
void clearLCD();
void initGlobal();
void bootloader();

#endif