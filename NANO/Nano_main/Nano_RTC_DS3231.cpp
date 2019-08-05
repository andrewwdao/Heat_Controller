/*-------------------------------------------
  RTC - header file
  ARDUINO NANO
  (c) Pham Thanh Tam - An Minh Dao 2019 
  version 1.10 - 05/08/2019
--------------------------------------------*/ 
#ifndef  __NANO_RTC_DS3231_H 
#define  __NANO_RTC_DS3231_H
#include "Nano_RTC_DS3231.h"

// ------ Private constants -----------------------------------
#define I2C_SDA A4
#define I2C_SCL A5
// ------ Private function prototypes -------------------------

// ------ Private variables -----------------------------------

// ------ PUBLIC variable definitions -------------------------
DS3231 rtc(I2C_SDA,I2C_SCL);
//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void RTC_init ()
{
    rtc.begin();
}//end RTC_init
//------------------------------------------
String RTC_getTime()
{ 
  String buffData="";
  Time t;
  t=rtc.getTime();
  buffData += t.hour; buffData += ":";
  buffData += t.min; buffData += "(";
  buffData += t.date; buffData +="/";
  buffData += t.mon; buffData += "/";
  buffData += t.year;
  Serial.println(buffData);
  return buffData;
}// end sentSD
#endif //__NANO_RTC_DS3231_H
