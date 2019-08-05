/*-------------------------------------------
SD-header file
ARDUINO NANO
(c) Pham Thanh Tam 
version 1.00 - 29/7/2019
--------------------------------------------*/
#ifndef  NANO_SD 
#define NANO_SD
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <DS3231.h>

// public function prototype 
void rece() ;// Receive data from serial and sent to SD
void rtc_init();// initial_rtc
void SD_init();
#endif // NANO_SD
