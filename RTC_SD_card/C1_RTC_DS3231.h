/*------------------------------------------------------------*-
  Module RTC using DS3231 - header file
  ESP32 CORE1 - APPLICATION CORE
  (c) An Minh Dao 2019
  version 1.30 - 10/02/2019
---------------------------------------------------------------
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
#ifndef _C1_RTC_DS3231_H
#define _C1_RTC_DS3231_H
#include "config.h"
#include "pins.h"
#include "Wire.h"
#include "RTClib.h"
#include <lwip/apps/sntp.h> //needed to access the internet time
#include <lwip/sockets.h> //needed for the ip converter
#include <time.h> //needed to use time function
#include "N_RAM_RTC.h"
#include "C0_Wifi_sta_ch.h"
// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
bool RTC_init();
String RTC_getTime();
String RTC_getDay();
String RTC_getClock();
uint8_t RTC_getSecond();
void RTC_Serial_updater();
void RTC_SNTP_updater();
// ------ Public variable -------------------------------------

#endif //_C1_RTC_DS3231_H