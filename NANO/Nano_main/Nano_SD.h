/*-------------------------------------------
  SD CARD - header file
  ARDUINO NANO
  (c) Pham Thanh Tam - An Minh Dao 2019 
  version 1.10 - 05/08/2019
--------------------------------------------*/ 
#ifndef  __NANO_SD_H 
#define  __NANO_SD_H
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <DS3231.h>

// public function prototype 
void rece() ;// Receive data from serial and sent to SD
void rtc_init();// initial_rtc
void SD_init();
#endif // __NANO_SD_H
