/*-------------------------------------------
  UART - header file
  ESP32 DEVKIT V1
  (c) Can Tho University 2019 
  version 1.10 - 26/08/2019
----------------------------------------------
 * All test function used with UART to USB has
 * to be in "No line ending" mode
 --------------------------------------------*/ 
#ifndef  __ESP32_UART_H 
#define  __ESP32_UART_H
#include <WiFi.h>
#include "ESP32_ADC.h"
#include "ESP32_NVS.h"
#include "ESP32_MQTT.h"
#include "debugConfig.h"
//#include "config.h"

// ------ Public constants ------------------------------------
#define AUTHORIZED_KEY "master ready! 070497"
// ------ Public function prototypes --------------------------
/**
Initialize UART
**/
void UART_init();
/**
Send signal to the slave when master is ready
**/
void UART_masterReady();
/**
Send current temp and flow values to slave to display to the LCD
**/
void UART_sendToSlave();
/**
Send current PID values to slave to display to the LCD
**/
void UART_PIDsendToSlave();
/**
Get the PID parameters, or the set temperatures, or the set flow sensor values from the slave
**/
void UART_getFromSlave();
// ------ Public variable -------------------------------------

#endif // __ESP32_UART_H
