/*------------------------------------------------------------*-
  Configuration file
  (c) Can Tho University 2019
  version 1.00 - 09/07/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef _CONFIG_H
#define _CONFIG_H

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////MODE CONFIGS/////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------
// USER DEFINE
// - SLASS OUT ANY OPTION THAT YOU DON'T WANT TO HAVE
//--------------------------------------------------------------
#define ESP32_DEBUG
#define WIFI_CHANGEABLE
#define SERIAL_OUTPUT
//#define TASKS_MONITOR //remember to change menuconfig when this is active
//--------------------------------------------------------------
// MAIN LIBRARY - WILL NEED TO EDIT THIS SECTION FOR EVERY PROJECT
//-------------------------------------------------------------
// Must include the appropriate microcontroller header file here
#include "WiFi.h" //for esp32
//--------------------------------------------------------------
// FLOW MAPPING
//--------------------------------------------------------------
#define FLOW_MIN 0    //put the mininum value of your flow sensor here
#define FLOW_MAX 100  //put the maximum value of your flow sensor here
//--------------------------------------------------------------
// TEMPERATURE MAPPING
//--------------------------------------------------------------
#define TEMP_MIN -10    //put the mininum value of your temperature sensor here -10
#define TEMP_MAX 860  //put the maximum value of your temperature sensor here +10
//--------------------------------------------------------------
// ADC
//--------------------------------------------------------------
#include <driver/adc.h>
#define FLOW_SEN01_PIN 36
#define FLOW_SEN02_PIN 39
#define TEMP_SEN01_PIN 34
#define TEMP_SEN02_PIN 35
#define TEMP_SEN03_PIN 32
#define TEMP_SEN04_PIN 33
//KALMAN FILTER PARAMETERS
#include <SimpleKalmanFilter.h>
#define FILTER_LAYER 3
#define E_MEA 3     //Measurement Uncertainty - How much do we expect to our measurement vary
#define E_EST 3     //Estimation Uncertainty - Can be initilized with the same value as e_mea since the kalman filter will adjust its value.
#define Q     0.007 //Process Variance - usually a small number between 0.001 and 1 - how fast your measurement moves. Recommended 0.01. Should be tunned to your needs.
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
