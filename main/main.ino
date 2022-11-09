// I'm the owner of the code (GitHub: @tesla15), this project uses GNU GPL license which means that you have to make your project open source GNU-GPL too when using code from my project, else you're robber.
// Have fun!

#include "lib.h"
#include "DHT.h"`

int current_mode = 0;
int lastState = LOW;
int statea;
int stateb;
int did_update = 0;

void setup() {
  initGlobal();
  initLCD();
  bootloader();
}

void mode_selector() {
  // selection of logic gate
  if (digitalRead(D7) == 0) {
    Serial.println("ESP: clicked D7 (mode selector)"); //debug
    if (lastState == LOW) {
      if (current_mode >= 5) {
        current_mode = 0;
        Serial.println("ESP: Mode set to 0 because of lack of next numbers");
      } else {
        current_mode++;
        Serial.println("ESP: Mode succesfully changed.");
      }
      lastState = HIGH;
    }
  } else {
    lastState = LOW;
  }
}

int calc_not() {
  int abut = digitalRead(D6);
  if (abut == 1) {
    return 1;
  } else {
    return 0;
  }
}

int calc_and() {
  int abut1 = digitalRead(D6);
  int bbut1 = digitalRead(D5);
  if (abut1 && bbut1 == 1) {
    return 0;
  }
  if (abut1 == 1 && bbut1 == 0) {
    return 0;
  }
  if (abut1 == 0 && bbut1 == 1) {
    return 0;
  }
  if (abut1 == 0 && bbut1 == 0) {
    return 1;
  }
}

int calc_or() {
  int abut1 = digitalRead(D6);
  int bbut1 = digitalRead(D5);
  if (abut1 && bbut1 == 1) {
    return 0;
  }
  if (abut1 == 1 && bbut1 == 0) {
    return 1;
  }
  if (abut1 == 0 && bbut1 == 1) {
    return 1;
  }
  if (abut1 == 0 && bbut1 == 0) {
    return 1;
  }
}

int calc_nor() {
  int abut1 = digitalRead(D6);
  int bbut1 = digitalRead(D5);
  if (abut1 && bbut1 == 1) {
    return 1;
  }
  if (abut1 == 1 && bbut1 == 0) {
    return 0;
  }
  if (abut1 == 0 && bbut1 == 1) {
    return 0;
  }
  if (abut1 == 0 && bbut1 == 0) {
    return 0;
  }
}

int calc_xor() {
  int abut1 = digitalRead(D6);
  int bbut1 = digitalRead(D5);
  if (abut1 && bbut1 == 1) {
    return 0;
  }
  if (abut1 == 1 && bbut1 == 0) {
    return 1;
  }
  if (abut1 == 0 && bbut1 == 1) {
    return 1;
  }
  if (abut1 == 0 && bbut1 == 0) {
    return 0;
  }
}

int calc_xnor() {
  int abut1 = digitalRead(D6);
  int bbut1 = digitalRead(D5);
  if (abut1 && bbut1 == 1) {
    return 1;
  }
  if (abut1 == 1 && bbut1 == 0) {
    return 0;
  }
  if (abut1 == 0 && bbut1 == 1) {
    return 0;
  }
  if (abut1 == 0 && bbut1 == 0) {
    return 1;
  }
}

void update_screen() {
  mode_selector();
  Serial.println(current_mode); //debug

  if (digitalRead(D6) == 0) {
    statea = 1;
  } else {                        //NOT operation on output from button.
    statea = 0;
  }
  
  if (digitalRead(D5) == 0) {
    stateb = 1;
  } else {                       //NOT operation on output from button.
    stateb= 0;
  }

  switch (current_mode) { //screen updating and stuff 
    case 0:
      printLCD(0,0, String(statea) + " --->");
     // printLCD(0,1, String(stateb) + " --->");     // NOT gate so 1 input.
      printLCD(7,0, "NOT");
      //printLCD(7,1, "NOT");
      printLCD(11,0,"--> " + String(calc_not()));
      break;
    case 1:
      printLCD(0,0, String(statea) + " --->");
      printLCD(0,1, String(stateb) + " --->");
      printLCD(7,0, "AND");
      printLCD(7,1, "AND");
      printLCD(11,0,"--> " + String(calc_and()));
      break;
    case 2:
      printLCD(0,0, String(statea) + " --->");
      printLCD(0,1, String(stateb) + " --->");
      printLCD(7,0, "OR");
      printLCD(7,1, "OR");
      printLCD(11,0,"--> " + String(calc_or()));
      break;
    case 3:
      printLCD(0,0, String(statea) + " --->");
      printLCD(0,1, String(stateb) + " --->");
      printLCD(7,0, "NOR");
      printLCD(7,1, "NOR");
      printLCD(11,0,"--> " + String(calc_nor()));
      break;
    case 4:
      printLCD(0,0, String(statea) + " --->");
      printLCD(0,1, String(stateb) + " --->");
      printLCD(7,0, "XOR");
      printLCD(7,1, "XOR");
      printLCD(11,0,"--> " + String(calc_xor()));
      break;
    case 5:
      printLCD(0,0, String(statea) + " --->");
      printLCD(0,1, String(stateb) + " --->");
      printLCD(7,0, "XNOR");
      printLCD(7,1, "XNOR");
      printLCD(11,0,"--> " + String(calc_xnor()));
      break;
  }
}


void loop() {
  if (digitalRead(D7) == 0) {
    clearLCD();
  }
  update_screen();
}

