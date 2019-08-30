/*-------------------------------------------
  RS232_485 - header file
  ESP32 DEVKIT V1
  (c) Can Tho University 2019 
  version 1.00 - 28/08/2019
 --------------------------------------------*/ 
#ifndef  __ESP32_RS232_485_H 
#define  __ESP32_RS232_485_H
#include <WiFi.h>
#include "debugConfig.h"
//#include "config.h"

// ------ Public constants ------------------------------------
#define AUTHORIZED_KEY "master ready! 070497"
// ------ Public function prototypes --------------------------
/**
Initialize UART
**/
void RS232_485_init();
/**
return true if signal is available
**/
bool RS232_available();
/**
write data to the second uart port, then it will be translated into 232 using the bit switches
**/
void RS232_write(String);
/**
read data from the second uart port (translated from the 232/485)
**/
char RS232_read();
/**
return true if signal is available
**/
bool RS485_available();
/**
write data to the second uart port, then it will be translated into 232 using the bit switches
**/
void RS485_write(String);
/**
read data from the second uart port (translated from the 232/485)
**/
char RS485_read();
// ------ Public variable -------------------------------------

#endif // __ESP32_RS232_485_H
