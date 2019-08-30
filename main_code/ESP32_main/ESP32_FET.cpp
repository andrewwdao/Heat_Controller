/*------------------------------------------------------------*-
  Power FET - functions file
  ESP32 DEVKIT V1
  (c) Can Tho University 2019
  version 1.00 - 28/08/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef __ESP32_FET_CPP
#define __ESP32_FET_CPP
#include "ESP32_FET.h"

// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------

// ------ Private variables -----------------------------------

// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void FET1_init() {
  pinMode(FET1_PIN, OUTPUT);
}//end FET1_init
//------------------------------------
void FET1pwm_init() { //max 16 independent pwm channel
  //output pwm
  ledcSetup(PWM_CHANNEL_5, PWM_FREQ, PWM_RES); // configure PWM chanel corresponding to frequency and resolution
  ledcAttachPin(FET1_PIN, PWM_CHANNEL_5);// attach the channel to the GPIO to be controlled
}//end FET1pwm_init
//------------------------------------
void FET1_ON() {
  digitalWrite(FET1_PIN,HIGH);
}//end FET1_ON
//------------------------------------
void FET1_OFF() {
  digitalWrite(FET1_PIN,LOW);
}//end FET1_OFF
//------------------------------------
void FET1pwm_write(int PWMpercentage) {
  ledcWrite(PWM_CHANNEL_5, PWMpercentage*PWM_RESOLUTION/100); //output signal to the pump
}//end FET1pwm_write
//------------------------------------
void FET2_init() {
  pinMode(FET2_PIN, OUTPUT);
}//end FET2_init
//------------------------------------
void FET2pwm_init() { //max 16 independent pwm channel
  //output pwm
  ledcSetup(PWM_CHANNEL_6, PWM_FREQ, PWM_RES); // configure PWM chanel corresponding to frequency and resolution
  ledcAttachPin(FET2_PIN, PWM_CHANNEL_6);// attach the channel to the GPIO to be controlled
}//end FET2pwm_init
//------------------------------------
void FET2_ON() {
  digitalWrite(FET2_PIN,HIGH);
}//end FET2_ON
//------------------------------------
void FET2_OFF() {
  digitalWrite(FET2_PIN,LOW);
}//end FET2_OFF
//------------------------------------
void FET2pwm_write(int PWMpercentage) {
  ledcWrite(PWM_CHANNEL_6, PWMpercentage*PWM_RESOLUTION/100); //output signal to the pump
}//end FET1pwm_write
//------------------------------------
#endif //__ESP32_FET_CPP
