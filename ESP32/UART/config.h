/*------------------------------------------------------------*-
  PWM Configuration file
  (c) Can Tho University 2019
  version 1.00 - 17/07/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef _CONFIG_H
#define _CONFIG_H

#define SERIAL_OUTPUT
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////MODE CONFIGS/////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------
// UART CONFIG
//--------------------------------------------------------------
#define MASTER_READY  3698
#define SLAVE_READY   7497
//--------------------------------------------------------------
// MAIN LIBRARY - WILL NEED TO EDIT THIS SECTION FOR EVERY PROJECT
//-------------------------------------------------------------
// Must include the appropriate microcontroller header file here
#include "WiFi.h" //for esp32

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ESP32_DEBUG // When this is active, every log will be execute.
  #ifndef SERIAL_OUTPUT
    #define SERIAL_OUTPUT
  #endif
  #ifndef WIFI_CHANGEABLE
    #define WIFI_CHANGEABLE
  #endif
  #ifndef SERIAL_BEGIN
    #define SERIAL_BEGIN()      {Serial.begin(115200);}
  #endif
  #define D_PRINT(...)       {Serial.print(__VA_ARGS__);}
  #define D_PRINTLN(...)     {Serial.println(__VA_ARGS__);}
  #define D_PRINTF(...)      {Serial.printf(__VA_ARGS__);}
#else
  #define D_PRINT(...)   {}
  #define D_PRINTLN(...) {}
  #define D_PRINTF(...)  {}
#endif

#ifdef WIFI_CHANGEABLE
  #ifndef SERIAL_BEGIN
    #define SERIAL_BEGIN()      {Serial.begin(115200);}
  #endif
#endif

#ifdef SERIAL_OUTPUT
  #ifndef SERIAL_BEGIN
    #define SERIAL_BEGIN()      {Serial.begin(115200);}
  #endif
  #define S_PRINT(...)       {Serial.print(__VA_ARGS__);}
  #define S_PRINTLN(...)     {Serial.println(__VA_ARGS__);}
  #define S_PRINTF(...)      {Serial.printf(__VA_ARGS__);}
#else
  #ifndef SERIAL_BEGIN
    #define SERIAL_BEGIN()  {}
  #endif
  #define S_PRINT(...)   {}
  #define S_PRINTLN(...) {}
  #define S_PRINTF(...)  {}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_CONFIG_H
