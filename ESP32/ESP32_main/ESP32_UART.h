/*-------------------------------------------
  UART - header file
  ESP32 DEVKIT V1
  (c) An Minh Dao - Pham Thanh Tam 2019 
  version 1.10 - 26/08/2019
--------------------------------------------*/ 
#ifndef  __ESP32_UART_H 
#define  __ESP32_UART_H
#include <Arduino.h>
#include "ESP32_ADC.h"
#include "debugConfig.h"
//#include "config.h"

// ------ Public constants ------------------------------------
#define AUTHORIZED_KEY "master ready! 070497\r\n"
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
Get the PID parameters, or the set temperatures, or the set flow sensor values from the slave
**/
void UART_getFromSlave();
// ------ Public variable -------------------------------------

#endif // __ESP32_UART_H
