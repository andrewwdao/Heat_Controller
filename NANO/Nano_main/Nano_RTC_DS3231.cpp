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
bool RTC_init()
{
    rtc.begin();
    return true;
}//end RTC_init
//------------------------------------------
String RTC_getTime()
{ 
  String rtcData="";
  Time t;
  t=rtc.getTime();
  rtcData += t.hour; rtcData += ":";
  rtcData += t.min; rtcData += "(";
  rtcData += t.date; rtcData +="/";
  rtcData += t.mon; rtcData += "/";
  rtcData += t.year; rtcData += ")";
  Serial.println(rtcData);
  return rtcData;
}// end RTC_getTime
#endif //__NANO_RTC_DS3231_H
