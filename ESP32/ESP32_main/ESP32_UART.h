/*-------------------------------------------
  UART - header file
  ESP32 DEVKIT V1
  (c) An Minh Dao - Pham Thanh Tam 2019 
  version 1.10 - 26/08/2019
--------------------------------------------*/ 
#ifndef  __ESP32_UART_H 
#define  __ESP32_UART_H
#include <Arduino.h>
#include "debugConfig.h"
//#include "config.h"

// ------ Public constants ------------------------------------
#define AUTHORIZED_KEY "kmaster ready! 070497\r\n"
// ------ Public function prototypes --------------------------
/**
Initialize UART
**/
void UART_init();
/**
Send confirmation to UART when master is ready
**/
void UART_masterReady();
/**
Collect the data from serial port if existed and send to SD
**/
void UART_getFromMaster();
/**
Send PID data to master
**/
void PIDsendToMaster(float*);
/**
Send temperature data to master
**/
void sTempSendToMaster(uint16_t*);
/**
Send flow data to master
**/
void sFlowSendToMaster(uint16_t*);
// ------ Public variable -------------------------------------

#endif // __ESP32_UART_H
