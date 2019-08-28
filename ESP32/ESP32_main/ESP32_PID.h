/*------------------------------------------------------------*-
  PID - header file
  ESP32 DEVKIT V1
  (c) An Minh Dao 2019
  version 1.00 - 14/08/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef __ESP32_PID_H
#define __ESP32_PID_H
#include <WiFi.h>

// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
/**
Read Kp value
*/
float PID_Kp_read();
/**
Read Ki value
*/
float PID_Ki_read();
/**
Read Kd value
*/
float PID_Kd_read();
/**
Fix Kp value
*/
float PID_Kp_write();
/**
Fix Ki value
*/
float PID_Ki_write();
/**
Fix Kd value
*/
float PID_Kd_write();
/**
PID calculation, return value from 0.01 to 1.
*/
float PIDcal(int,int);
// ------ Public variable -------------------------------------

#endif //__ESP32_PID_H
