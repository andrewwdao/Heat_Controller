/*------------------------------------------------------------*-
  debug - function file
  ESP32 DEVKIT V1
  (c) Can Tho University - 2019
  version 1.00 - 23/10/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef  __ESP32_DEBUG_CPP
#define  __ESP32_DEBUG_CPP
#include "ESP32_debug.h"

// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------

// ------ Private variables -----------------------------------

// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void debug_init() {
  vSemaphoreCreateBinary(baton); //initialize binary semaphore //baton = xSemaphoreCreateBinary(); //this works too but not as good as the current use

  UART_init();
  ADC_init();
  PID_init();
  pump1_init();
  pump2_init();
  relay_init();
  UART_masterReady();
  core0_init(); //must stand above MQTT init
  
  xSemaphoreTake(baton, portMAX_DELAY); // ( TickType_t ) and portTICK_PERIOD_MS is also available , view: http://esp32.info/docs/esp_idf/html/d1/d19/group__xSemaphoreTake.html 
  xSemaphoreGive(baton);
}//end debug_init
//------------------------------------------------------------
void system_debug() {
//  CONTROL RELAY LIKE THIS
//   relay01(ON);
//   relay02(OFF);
//   relay03(OFF);
    

//  READ VALUE FROM THE MEMORY LIKE THIS
//   Serial.println(NVS_read_Kp());
//   Serial.println(NVS_read_Ki());
//   Serial.println(NVS_read_Kd());
//   Serial.println(NVS_read_T1());
//   Serial.println(NVS_read_T2());
//   Serial.println(NVS_read_T3());
//   Serial.println(NVS_read_T4());
//   Serial.println(NVS_read_F1());
//   Serial.println(NVS_read_F2());
//   delay(5000);
//  PUBLISH THE TEMPERATURE LIKE THIS
//   MQTT_T1_pub(31);//tempSen01_read()
//   MQTT_T2_pub(35);//tempSen02_read()
//   MQTT_T3_pub(33);//tempSen03_read()
//   MQTT_T4_pub(30);//tempSen04_read()
//   you can put any value as you want like this
//   MQTT_T1_pub(123); 

//  PUBLISH THE PUMP PWM FREQ LIKE THIS
//   MQTT_Pump1pwm_pub(pump1pwm_read());
//   MQTT_Pump2pwm_pub(pump2pwm_read());

}//end system_debug

#endif // __ESP32_DEBUG_CPP
