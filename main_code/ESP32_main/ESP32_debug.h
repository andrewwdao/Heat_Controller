/*------------------------------------------------------------*-
  debug - header file
  ESP32 DEVKIT V1
  (c) Can Tho University - 2019
  version 1.00 - 23/10/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef  __ESP32_DEBUG_H 
#define  __ESP32_DEBUG_H 
#include "ESP32_ADC.h"
#include "ESP32_PID.h"
#include "ESP32_PWM_Pump.h"
#include "ESP32_UART.h"
#include "ESP32_relay.h"
#include "ESP32_MQTT.h"
#include "ESP32_NVS.h"
#include "ESP32_FET.h"
#include "ESP32_core0.h"

// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
/**
Initialize of the system
**/
void debug_init();
/**
Main routine of the system
**/
void system_debug();
// ------ Public variable -------------------------------------
extern SemaphoreHandle_t baton;
#endif // __ESP32_DEBUG_H 