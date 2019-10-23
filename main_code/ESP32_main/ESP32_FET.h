/*------------------------------------------------------------*-
  Power FET - header file
  ESP32 DEVKIT V1
  (c) Can Tho University 2019
  version 1.00 - 28/08/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef __ESP32_FET_H
#define __ESP32_FET_H
#include <WiFi.h>
#include "ESP32_PWM_Pump.h"
#include "debugConfig.h"

// ------ Public constants ------------------------------------
#define FET1_PIN  12
#define FET2_PIN  13
//PWM Channels - max 16 independent channels
#define PWM_CHANNEL_5 4
#define PWM_CHANNEL_6 5
// ------ Public function prototypes --------------------------
/**
Initialize FET 1 as an on/off output
*/
void FET1_init();
/**
Initialize FET 1 as an pwm output
*/
void FET1pwm_init();
/**
ON FET 1
*/
void FET1_ON();
/**
OFF FET 1
*/
void FET1_OFF();
/**
create pulse for FET 1 - goes from 0 to 100
*/
void FET1pwm_write(int);
/**
Initialize FET 2 as an on/off output
*/
void FET2_init();
/**
Initialize FET 1 as an pwm output
*/
void FET2pwm_init();
/**
ON FET 2
*/
void FET2_ON();
/**
OFF FET 2
*/
void FET2_OFF();
/**
create pulse for FET 2 - goes from 0 to 100
*/
void FET2pwm_write(int);
// ------ Public variable -------------------------------------

#endif //__ESP32_FET_H
