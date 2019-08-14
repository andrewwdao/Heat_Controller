/*------------------------------------------------------------*-
  MAIN - functions file
  ESP32 DEVKIT V1
  (c) An Minh Dao - 2019
  version 1.00 - 14/08/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#include "ESP32_ADC.h"
#include "ESP32_PID.h"
#include "ESP32_PWM_Pump.h"
#include "ESP32_UART.h"
#include "ESP32_relay.h"
void setup() 
{
  //UART_init();
  ADC_init();
  pump1_init();
  pump2_init();
  relay_init();
}// end setup

void loop() 
{

}//end loop
