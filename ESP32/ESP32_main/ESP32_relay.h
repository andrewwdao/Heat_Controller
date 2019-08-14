/*------------------------------------------------------------*-
  RELAY configuration - header file
  ESP32 DEVKIT V1
  (c) An Minh Dao 2019
  version 1.00 - 14/08/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef __ESP32_RELAY_H
#define __ESP32_RELAY_H
#include <WiFi.h> //for esp32
//#include "config.h"

// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
/**
Initialize relay
**/
void relay_init();
/**
Configure relay 01
**/
void relay01(bool);
/**
Configure relay 02
**/
void relay02(bool);
/**
Configure relay 03
**/
void relay03(bool);
// ------ Public variable -------------------------------------

#endif //__ESP32_RELAY_H
