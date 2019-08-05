/*------------------------------------------------------------*-
  MAIN - functions file
  ARDUINO NANO
  (c) An Minh Dao - Pham Thanh Tam - 2019
  version 1.30 - 05/08/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  
 *  
 *  PRIVATE FUNCTIONS CONTAIN:
 *  
 * 
 --------------------------------------------------------------*/
#include "Nano_LCD.h"
#include "Nano_SD.h"

void setup() 
{
 LCD_init();
 Serial.begin(115200);
 rtc_init();
 SD_init();
}// end setup



void loop() {
  LCD_display();
  rece();
}
