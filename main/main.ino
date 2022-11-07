#include "lib.h"

void setup() {
  initGlobal();
  initLCD();
}

void loop() {
  printLCD(0,0,"................");
  printLCD(0,1,"................");
}
