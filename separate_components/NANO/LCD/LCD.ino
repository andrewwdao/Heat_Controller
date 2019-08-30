/*------------------------------------------------------------*-
  LCD - functions file
  ARDUINO NANO
  (c) Can Tho University 2019
  version 1.00 - 26/07/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  
 *  
 *  PRIVATE FUNCTIONS CONTAIN:
 *  
 * 
 --------------------------------------------------------------*/
#include "Nano_LCD.h"

void setup() {
 LCD_init();
 Serial.begin(115200);
}

void loop() {
  LCD_display();
}
