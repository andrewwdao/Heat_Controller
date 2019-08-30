/*------------------------------------------------------------*-
  NVS - non volatile system - header file
  ESP32 DEVKIT V1
  (c) Can Tho University 2019
  version 1.00 - 27/08/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef _ESP32_NVS_H
#define _ESP32_NVS_H
#include "config.h"
#include "Preferences.h" // this library save in NVS - non volatile storage memory (in flash! not EEPROM, perfect!)
#include <nvs.h>
#include <nvs_flash.h>
// ------ Public constants ------------------------------------

// ------ Public function prototypes --------------------------
/**
Write PID parameters to the NVS
**/
void NVS_PID_write(float,float,float);
/**
Read PID parameters: Kp
**/
float NVS_read_Kp();
/**
Read PID parameters: Ki
**/
float NVS_read_Ki();
/**
Read PID parameters: Kd
**/
float NVS_read_Kd();
/**
Write the set temperatures to the NVS
**/
void NVS_Temp_write(int,int,int,int);
/**
Read the set Temperature
**/
int NVS_read_T1();
/**
Read the set Temperature
**/
int NVS_read_T2();
/**
Read the set Temperature
**/
int NVS_read_T3();
/**
Read the set Temperature
**/
int NVS_read_T4();
/**
Write the set flow values to the NVS
**/
void NVS_Flow_write(int,int);
/**
Read the set Flow
**/
int NVS_read_F1();
/**
Read the set Flow
**/
int NVS_read_F2();
// ------ Public variable -------------------------------------

#endif //_ESP32_NVS_H
