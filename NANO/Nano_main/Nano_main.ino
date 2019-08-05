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
#include "Nano_RTC_DS3231.h"
void setup() 
{
 LCD_init();
 Serial.begin(115200);
 RTC_init();
 SD_init();
}// end setup



void loop() {
  LCD_display();
  rece();
}
