/*------------------------------------------------------------*-
  MAIN - functions file
  ARDUINO NANO
  (c) Can Tho University - 2019
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
   Serial.println("begin");
 // UART_isMasterReady();
  Serial.println(" ready");
}// end setup

void loop() 
{
// LCD_display();
// UART_getFromMaster();
 RTC_getTime();
 Serial.println(" end");
// Serial.println(rtcData);
}//end loop
