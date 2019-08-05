/*-------------------------------------------
  RTC DS3231 - header file
  ARDUINO NANO
  (c) An Minh Dao - Pham Thanh Tam 2019 
  version 1.10 - 05/08/2019
--------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void RTC_init();
 *  void RTC_setTime(); //only exist on DEBUG MODE
 *  void RTC_setCurrentTime();
 *  void RTC_getTime();
 *   
 *  PRIVATE FUNCTIONS CONTAIN:
 *  String RTC_GetData(); //only exist on DEBUG MODE
 * 
 *  CAUTION: must include config.h
 --------------------------------------------------------------*/
#ifndef _NANO_RTC_DS3231_H
#define _NANO_RTC_DS3231_H
#include <Arduino.h>
#include <DS3231.h>

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
