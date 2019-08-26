/*------------------------------------------------------------*-
  MAIN - functions file
  ARDUINO NANO
  (c) An Minh Dao - Pham Thanh Tam - 2019
  version 1.30 - 05/08/2019
---------------------------------------------------------------*/
#include "Nano_LCD.h"
#include "Nano_SD.h"
#include "Nano_RTC_DS3231.h"
#include "Nano_UART.h"
void setup() 
{
  UART_init();
  LCD_init();
  RTC_init();
  SD_init();
  
  UART_isMasterReady();
}// end setup

void loop() 
{
 LCD_display();
 getFromMaster();
}//end loop
