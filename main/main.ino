// I'm the owner of the code (GitHub: @tesla15), this project uses GNU GPL license which means that you have to make your project open source GNU-GPL too when using code from my project, else you're robber.
// Have fun!

#include "lib.h"


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
      if (current_mode >= 6) {
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

void handleLED() {
  if (digitalRead(D6) == 0) {
    digitalWrite(D0, HIGH);
  } else {
    digitalWrite(D0, LOW);
  }
  if (digitalRead(D5) == 0) {
    digitalWrite(D3, HIGH);
  } else {
    digitalWrite(D3, LOW);
  }
}

int calc_not() {
  int abut = digitalRead(D6);
  if (abut == 1) {
    digitalWrite(D9, HIGH);
    return 1;
  } else {
    digitalWrite(D9, LOW);
    return 0;
  }
}

int calc_and() {
  int abut1 = digitalRead(D6);
  int bbut1 = digitalRead(D5);
  if (abut1 && bbut1 == 1) {
    digitalWrite(D9, LOW);
    return 0;
    
  }
  if (abut1 == 1 && bbut1 == 0) {
    digitalWrite(D9, LOW);
    return 0;
    
  }
  if (abut1 == 0 && bbut1 == 1) {
    digitalWrite(D9, LOW);
    return 0;
    
  }
  if (abut1 == 0 && bbut1 == 0) {
    digitalWrite(D9, HIGH);
    return 1;
  }
}

int calc_nand() {
  int abut1 = digitalRead(D6);
  int bbut1 = digitalRead(D5);
  if (abut1 && bbut1 == 1) {
    digitalWrite(D9, HIGH);
    return 1;
    
  }
  if (abut1 == 1 && bbut1 == 0) {
    digitalWrite(D9, HIGH);
    return 1;
    
  }
  if (abut1 == 0 && bbut1 == 1) {
    digitalWrite(D9, HIGH);
    return 1;
    
  }
  if (abut1 == 0 && bbut1 == 0) {
    digitalWrite(D9, LOW);
    return 0;
  }
}

int calc_or() {
  int abut1 = digitalRead(D6);
  int bbut1 = digitalRead(D5);
  if (abut1 && bbut1 == 1) {
    digitalWrite(D9, LOW);
    return 0;
    
  }
  if (abut1 == 1 && bbut1 == 0) {
     digitalWrite(D9, HIGH);
    return 1;
   
  }
  if (abut1 == 0 && bbut1 == 1) {
     digitalWrite(D9, HIGH);
    return 1;
   
  }
  if (abut1 == 0 && bbut1 == 0) {
     digitalWrite(D9, HIGH);
    return 1;
   
  }
}

int calc_nor() {
  int abut1 = digitalRead(D6);
  int bbut1 = digitalRead(D5);
  if (abut1 && bbut1 == 1) {
    digitalWrite(D9, HIGH);
    return 1;
    
  }
  if (abut1 == 1 && bbut1 == 0) {
    digitalWrite(D9, LOW);
    return 0;
  }
  if (abut1 == 0 && bbut1 == 1) {
    digitalWrite(D9, LOW);
    return 0;
    
  }
  if (abut1 == 0 && bbut1 == 0) {
    digitalWrite(D9, LOW);
    return 0;
    
  }
}

int calc_xor() {
  int abut1 = digitalRead(D6);
  int bbut1 = digitalRead(D5);
  if (abut1 && bbut1 == 1) {
    digitalWrite(D9, HIGH);
    return 0;
    
  }
  if (abut1 == 1 && bbut1 == 0) {
    digitalWrite(D9, HIGH);
    return 1;
    
  }
  if (abut1 == 0 && bbut1 == 1) {
     digitalWrite(D9, HIGH);
    return 1;
   
  }
  if (abut1 == 0 && bbut1 == 0) {
    digitalWrite(D9, LOW);
    return 0;
    
  }
}

int calc_xnor() {
  int abut1 = digitalRead(D6);
  int bbut1 = digitalRead(D5);
  if (abut1 && bbut1 == 1) {
    digitalWrite(D9, HIGH);
    return 1;
    
  }
  if (abut1 == 1 && bbut1 == 0) {
    digitalWrite(D9, LOW);
    return 0;
    
  }
  if (abut1 == 0 && bbut1 == 1) {
    digitalWrite(D9, LOW);
    return 0;
    
  }
  if (abut1 == 0 && bbut1 == 0) {
    digitalWrite(D9, HIGH);
    return 1;
    
  }
}

void update_screen() {
  handleLED();
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
      printLCD(0,1, String(statea) + " ---->");
     // printLCD(0,1, String(stateb) + " --->");     // NOT gate so only one input.
      printLCD(8,1, "NOT");
      //printLCD(7,1, "NOT");
      printLCD(12,1,"----> " + String(calc_not()));
      break;
    case 1:
      printLCD(0,1, String(statea) + " ----> ");
      printLCD(0,2, String(stateb) + " ---->" );
      printLCD(8,1, "AND");
      printLCD(8,2, "AND");
      printLCD(12,1,"---> " + String(calc_and()));
      break;
    case 2:
      printLCD(0,1, String(statea) + " ---->");
      printLCD(0,2, String(stateb) + " ---->");
      printLCD(8,1, "NAND");
      printLCD(8,2, "NAND");
      printLCD(14,1,"---> " + String(calc_nand()));
      break;
    case 3:
      printLCD(0,1, String(statea) + " ---->");
      printLCD(0,2, String(stateb) + " ---->");
      printLCD(8,1, "OR");
      printLCD(8,2, "OR");
      printLCD(12,1,"-----> " + String(calc_or()));
      break;
    case 4:
      printLCD(0,1, String(statea) + " ---->");
      printLCD(0,2, String(stateb) + " ---->");
      printLCD(8,1, "NOR");
      printLCD(8,2, "NOR");
      printLCD(12,1,"---> " + String(calc_nor()));
      break;
    case 5:
      printLCD(0,1, String(statea) + " ---->");
      printLCD(0,2, String(stateb) + " ---->");
      printLCD(8,1, "XOR");
      printLCD(8,2, "XOR");
      printLCD(12,1,"---> " + String(calc_xor()));
      break;
    case 6:
      printLCD(0,1, String(statea) + " ---->");
      printLCD(0,2, String(stateb) + " ---->");
      printLCD(8,1, "XNOR");
      printLCD(8,2, "XNOR");
      printLCD(14,1,"---> " + String(calc_xnor()));
      break;
  }
}


void loop() {
  if (digitalRead(D7) == 0) {
    clearLCD();
  }
  update_screen();
}

