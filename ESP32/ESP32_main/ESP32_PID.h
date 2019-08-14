/*------------------------------------------------------------*-
  PID - header file
  ESP32 DEVKIT V1
  (c) An Minh Dao 2019
  version 1.00 - 14/08/2019
---------------------------------------------------------------*/
#ifndef __ESP32_PID_H
#define __ESP32_PID_H
#include <WiFi.h>


// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
/**
PID calculation, return value from 0.01 to 1.
*/
void PIDcal();
// ------ Public variable -------------------------------------

#endif //__ESP32_PID_H
