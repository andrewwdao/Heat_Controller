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
#include "Nano_RTC_DS3231.h"
#include "debugConfig.h"
//#include "config.h"

// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
/**
Initialize SD card
**/
bool SD_init();
/**
Collect the data from serial port if existed and send to SD
**/
void getFromMaster();
// ------ Public variable -------------------------------------

#endif // __NANO_SD_H
