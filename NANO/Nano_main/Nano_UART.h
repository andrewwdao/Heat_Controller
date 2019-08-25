/*-------------------------------------------
  UART - header file
  ARDUINO NANO
  (c) An Minh Dao - Pham Thanh Tam 2019 
  version 1.10 - 25/08/2019
--------------------------------------------*/ 
#ifndef  __NANO_UART_H 
#define  __NANO_UART_H
#include <Arduino.h>
#include "Nano_SD.h"
#include "debugConfig.h"
//#include "config.h"

// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
/**
Initialize UART
**/
void UART_init();
/**
Collect the data from serial port if existed and send to SD
**/
void getFromMaster();
// ------ Public variable -------------------------------------

#endif // __NANO_UART_H
