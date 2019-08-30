/*-------------------------------------------
  SD CARD - header file
  ARDUINO NANO
  (c) Can Tho University 2019 
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
Send data to SD as: temp1, temp2, temp3, temp4, flow1, flow2
**/
void sendSD(int,int,int,int,int,int);
// ------ Public variable -------------------------------------

#endif // __NANO_SD_H
