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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////MODE CONFIGS/////////////////////////////////////////////////////////////////////
#define GRUNDFOS_UPM3_PWM
  #define PROFILE_A_HEATING
  //#define PROFILE_C_SOLAR
//#define YONOS_PARA_ST_15/13_PWM2
//--------------------------------------------------------------
// MAIN LIBRARY - WILL NEED TO EDIT THIS SECTION FOR EVERY PROJECT
//-------------------------------------------------------------
// Must include the appropriate microcontroller header file here
#include "WiFi.h" //for esp32
//--------------------------------------------------------------
// CHOOSING PUMP
//--------------------------------------------------------------
#ifdef GRUNDFOS_UPM3_PWM
  #define PWM_FREQ  500  //The square-wave PWM signal is designed for a 100 to 4,000 Hz frequency range.
  #ifdef PROFILE_A_HEATING
    #define MAX_SPEED           0.05*PWM_RESOLUTION   // < 10%, so 5% will be enough
    #define MIN_SPEED           0.87*PWM_RESOLUTION   // >84% / <91% --> choose 87%
    #define VAR_MAXSPEED        0.83*PWM_RESOLUTION   // <=84% --> choose 83%
    #define VAR_MINSPEED        0.11*PWM_RESOLUTION   // >10% --> choose 11%
    #define HYSTERESIS_ON/OFF   0.93*PWM_RESOLUTION   // >91% and <95% --> choose 93%
    #define STANDBY_MODE_OFF    0.97*PWM_RESOLUTION   // >95% and <100% --> choose 97%
  #endif
  #ifdef PROFILE_C_SOLAR
    #define MAX_SPEED           0.95*PWM_RESOLUTION   // >90% and <= 100%, so 95% will be enough
    #define MIN_SPEED           0.13*PWM_RESOLUTION   // >8% / <15% --> choose 13%
    #define VAR_MAXSPEED        0.89*PWM_RESOLUTION   // <=90% --> choose 89%
    #define VAR_MINSPEED        0.16*PWM_RESOLUTION   // >15% --> choose 16%
    #define HYSTERESIS_ON/OFF   0.07*PWM_RESOLUTION   // >5% and <8% --> choose 7%
    #define STANDBY_MODE_OFF    0.03*PWM_RESOLUTION   // <5% --> choose 3%
  #endif
#endif

//--------------------------------------------------------------
// PUMP PARAMETERS
//--------------------------------------------------------------
#define PUMP1_OUT_PIN 25
#define PUMP1_IN_PIN  26
#define PUMP2_OUT_PIN 27
#define PUMP2_IN_PIN  14

//PWM Channels - max 16 independent channels
#define PWM_CHANNEL_1 0
#define PWM_CHANNEL_2 1
#define PWM_CHANNEL_3 2
#define PWM_CHANNEL_4 3

#define PWM_RES 13 // 13 bit resolution = 2^13-1 = 8191 propotion
#define PWM_RESOLUTION  8191 // 2^13-1
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
