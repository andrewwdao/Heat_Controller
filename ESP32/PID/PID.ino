/*------------------------------------------------------------*-
  PID - functions file
  ESP32 DEVKIT V1
  (c) An Minh Dao 2019
  version 1.00 - 14/08/2019
---------------------------------------------------------------*/
#ifndef __ESP32_PID_CPP
#define __ESP32_PID_CPP
#include "PID.h"

// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------

// ------ Private variables -----------------------------------
float previous_error = 0;
uint32_t lastTime = millis();
//PID constants:
int kp = 9.1;
int ki = 0.3;
int kd = 1.8;
// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
float PIDcal(int setVal,int realVal) {
  float elapsedTime, timePrev;
  int PID_value = 0;
  int PID_p = 0;    
  int PID_i = 0;
  int PID_d = 0;
  //We calculate the error between the setpoint and the real value
  float PID_error = setVal - realVal;
  //Calculate the P value
  PID_p = kp * PID_error;
  //Calculate the I value in a range on +-3
  if(-3 < PID_error <3) {PID_i = PID_i + (ki * PID_error);}

  //For derivative we need real time to calculate speed change rate
  timePrev = lastTime; // the previous time is stored before the actual time read
  lastTime = millis(); // actual time read
  elapsedTime = (lastTime - timePrev) / 1000; 
  //Now we can calculate the D calue
  PID_d = kd*((PID_error - previous_error)/elapsedTime);
  //Final total PID value is the sum of P + I + D
  PID_value = PID_p + PID_i + PID_d;

  //We define PID range between 0 and 1000
  if(PID_value < 0)   {PID_value = 0;}
  if(PID_value > 1000){PID_value = 1000;}
  //Remember to store the previous error for next loop.
  previous_error = PID_error;  

  return (PID_value/100000); //to make return value goes from 0.01 to 1
}//end PID_cal

void setup() {}
void loop() {}

#endif //__ESP32_PID_CPP
