/*------------------------------------------------------------*-
  MAIN - functions file
  ESP32 DEVKIT V1
  (c) Can Tho University - 2019
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
#include "ESP32_MQTT.h"
#include "ESP32_NVS.h"
#include "ESP32_FET.h"
#include "ESP32_core0.h"

SemaphoreHandle_t baton; //baton to make a core waiting for another core when needed
///////////////////////////////////////MAIN FUNCTION/////////////////////////////////////
void setup() 
{
 //---------------------------------- SETUP PROTOCOL -------------------------------------------
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
 //------------------------------- END SETUP PROTOCOL --------------------------------------------
  
    //CONTROL RELAY LIKE THIS
    relay01(ON);
    relay02(OFF);
    relay03(OFF);
    
    //READ VALUE FROM THE FLASH LIKE THIS
//    Serial.println(NVS_read_Kp());
//    Serial.println(NVS_read_Ki());
//    Serial.println(NVS_read_Kd());
//    Serial.println(NVS_read_T1());
//    Serial.println(NVS_read_T2());
//    Serial.println(NVS_read_T3());
//    Serial.println(NVS_read_T4());
//    Serial.println(NVS_read_F1());
//    Serial.println(NVS_read_F2());
  delay(5000);
    //PUBLISH THE TEMPERATURE LIKE THIS
    MQTT_T1_pub(tempSen01_read());
    MQTT_T2_pub(tempSen02_read());
    MQTT_T3_pub(tempSen03_read());
    MQTT_T4_pub(tempSen04_read());
    //you can put any value as you want like this
    //MQTT_T1_pub(123); 

    //PUBLISH THE PUMP PWM FREQ LIKE THIS
//    MQTT_Pump1pwm_pub(pump1pwm_read());
//    MQTT_Pump2pwm_pub(pump2pwm_read());

}// end setup

void loop() 
{
  UART_getFromSlave();
  mainRoutine();
  //UART_sendToSlave(10); //send data to slave every 10 second - you can change the interval as you want
}//end loop

/*put your code here to fit your system*/
void mainRoutine() {
  if (tempSen01_read()<50) { //if T_Collector< 50 celcius degree
    pump1_OFF();
  }//end if
  if (tempSen01_read()>60) { //if T_Collector>60 and 
    if ((tempSen02_read()>80)|(tempSen03_read()>50)) { //(T_Buffer1>80 or T_Buffer2>50) --> slower
      pump1_slower(PIDcal(NVS_read_T2(),tempSen02_read())); //setval - realval
    }//end if
    if ((tempSen02_read()<80)&(tempSen03_read()>50)) { //(T_Buffer1<80 and T_Buffer2>50) --> slower
      pump1_slower(PIDcal(NVS_read_T2(),tempSen02_read())); //setval - realval
    }//end if
    if ((tempSen02_read()<80)&(tempSen03_read()<50)) { //(T_Buffer1<80 and T_Buffer2<50) --> higher
      pump1_faster(PIDcal(NVS_read_T2(),tempSen02_read())); //setval - realval
    }//end if
  }//end if
}//end mainRoutine
