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
#include "ESP32_MQTT.h"
#include "ESP32_NVS.h"
#include "ESP32_FET.h"
///////////////////////////////////////MAIN FUNCTION/////////////////////////////////////
void setup() 
{
  UART_init();
  ADC_init();
  pump1_init();
  pump2_init();
  relay_init();
  MQTT_init();

  UART_masterReady();
    //publishNow(temp01,134,RETAIN,"Temp01 Failed!","Temp01 updated!");
    //publishNow(temp02,216,RETAIN,"Temp02 Failed!","Temp02 updated!");
    //publishNow(temp03,368,RETAIN,"Temp03 Failed!","Temp03 updated!");
    //publishNow(temp04,489,RETAIN,"Temp04 Failed!","Temp04 updated!");
//    Serial.println(NVS_read_Kp());
//    Serial.println(NVS_read_Ki());
//    Serial.println(NVS_read_Kd());
//    Serial.println(NVS_read_T1());
//    Serial.println(NVS_read_T2());
//    Serial.println(NVS_read_T3());
//    Serial.println(NVS_read_T4());
//    Serial.println(NVS_read_F1());
//    Serial.println(NVS_read_F2());
}// end setup

void loop() 
{
  MQTT_maintain();
  UART_getFromSlave();

  mainRoutine();
  //UART_sendToSlave();
  //relay01(ON);
//  relay03(OFF);
  //relay01(OFF);

}//end loop

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
