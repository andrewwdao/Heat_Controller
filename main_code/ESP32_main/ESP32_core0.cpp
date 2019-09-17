/*------------------------------------------------------------*-
  ESP32 CORE0 COMBINED TASK - PROTOCOL CORE - functions file
  COMBINED LOCATION FOR INTERACTING BETWEEN FILES
  (c) An Minh Dao 2019
  version 1.20 - 10/02/2019
---------------------------------------------------------------
 *  CAUTION:
 *  This core is responsible for RF radio, Wifi stack and protocols (watchdog,...) 
 *  (the Arduino code is compiled to run on the second core (core_1). FreeRTOS manages everything)
 *  Therefore, you have to be EXTREMELY CAREFUL when create task for this core,
 *  in order to not intefere these default functions (watchdog has the piority of 1 among 0 to N, higher number means higer piority)
 --------------------------------------------------------------*/
#ifndef __ESP32_CORE0_CPP
#define __ESP32_CORE0_CPP
#include "ESP32_core0.h"

// ------ Private constants -----------------------------------
#define C0_TASK_STACK   15000 // Stack size of Task1_CORE0 (in bytes- NOT words)
#define DEFAULT_PIORITY 0
// ------ Private function prototypes -------------------------
static void Core0Task( void * parameter ); //task run on core0
/*
  xSemaphoreGive(serialLog_baton);
  xSemaphoreTake(serialLog_baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
*/
// ------ Private variables -----------------------------------
TaskHandle_t Core0_handle; //pointer
// ------ PUBLIC variable definitions -------------------------
extern SemaphoreHandle_t baton;
//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void core0_init() {
  xTaskCreatePinnedToCore(
    Core0Task,                           /* Task Function */
    "C0_MQTTsub",                        /* Name of Task */
    C0_TASK_STACK,                       /* Stack size of Task - in bytes (in normal FREERTOS it will be words)*/
    NULL,                                /* Parameter of the task */
    DEFAULT_PIORITY,                     /* Priority of the task, vary from 0 to N, bigger means higher piority, need to be 0 to be lower than the watchdog*/
    &Core0_handle,                       /* Task handle to keep track of created task */
    PRO_CPU_NUM);                        /* CoreID - CORE0: 0 or PRO_CPU_NUM - CORE1: 1 or APP_CPU_NUM - tskNO_AFFINITY: either one is free*/
}//end Core0_init

static void Core0Task( void * parameter ) {//usual task run on core0 
  xSemaphoreTake(baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
  MQTT_init();
  xSemaphoreGive(baton);
//////////////////////////////LOOP////////////////////////////////////////////////////
  while (1) {
    MQTT_maintain();
    MQTT_subscribe();
  }//end while loop
}//end Core0Task
#endif //__ESP32_CORE0_CPP
