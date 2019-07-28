/*------------------------------------------------------------*-
  LCD - functions file
  ARDUINO NANO
  (c) Pham Thanh Tam - An Minh Dao 2019
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
