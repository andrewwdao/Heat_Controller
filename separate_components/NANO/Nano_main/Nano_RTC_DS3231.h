/*-------------------------------------------
  RTC DS3231 - header file
  ARDUINO NANO
  (c) Can Tho University 2019 
  version 1.10 - 05/08/2019
--------------------------------------------*/
#ifndef _NANO_RTC_DS3231_H
#define _NANO_RTC_DS3231_H
#include <Arduino.h>
#include <DS3231.h>
#include "debugConfig.h"
//#include "config.h"

// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
/**
Initialize RTC
**/
bool RTC_init();
/**
Get time from the RTC
**/
String RTC_getTime();
// ------ Public variable -------------------------------------

#endif // __NANO_RTC_DS3231_H
