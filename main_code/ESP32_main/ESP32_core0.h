/*------------------------------------------------------------*-
  ESP32 CORE0 COMBINED TASK - PROTOCOL CORE - header file
  ESP32 DEVKIT V1
  (c) Can Tho University 2019
  version 1.00 - 10/09/2019
---------------------------------------------------------------
 *  CAUTION:
 *  This core is responsible for RF radio, Wifi stack and protocols (watchdog,...) 
 *  (the Arduino code is compiled to run on the second core (core_1). FreeRTOS manages everything)
 *  Therefore, you have to be EXTREMELY CAREFUL when create task for this core,
 *  in order to not intefere these default functions (watchdog has the piority of 1 among 0 to N, higher number means higer piority)
 * 
 --------------------------------------------------------------*/
#ifndef __ESP32_CORE0_H
#define __ESP32_CORE0_H
//#include "config.h"
#include "ESP32_MQTT.h"
#include "ESP32_relay.h"
#include "ESP32_PID.h"
// ------ Public constants ------------------------------------

// ------ Public function prototypes -------------------------
/**
Initialize core0 for MQTT subcribing
**/
void core0_init();
/*
  xSemaphoreGive(serialLog_baton);
  xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
*/

// ------ Public variable -------------------------
extern SemaphoreHandle_t baton; //declared in core0 cpp
//SUBCRIBE
extern Adafruit_MQTT_Subscribe sub_kp;
extern Adafruit_MQTT_Subscribe sub_ki;
extern Adafruit_MQTT_Subscribe sub_kd;
extern Adafruit_MQTT_Subscribe sub_pump1pwm;
extern Adafruit_MQTT_Subscribe sub_pump2pwm;
extern Adafruit_MQTT_Subscribe sub_relay01;
extern Adafruit_MQTT_Subscribe sub_relay02;
extern Adafruit_MQTT_Subscribe sub_relay03;

#endif //__ESP32_CORE0_H
