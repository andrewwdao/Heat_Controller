/*-------------------------------------------
  ADC Converter - function file
  ESP32 DEVKIT V1
  (c) Can Tho University - 2019 
  version 1.00 - 14/08/2019
--------------------------------------------*/ 
/*
  AnalogRead Serial
  https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
  ADC_0db: sets no attenuation (1V input = ADC reading of 1088).
  ADC_2_5db: sets an attenuation of 1.34 (1V input = ADC reading of 2086).
  ADC_6db: sets an attenuation of 1.5 (1V input = ADC reading of 2975).
  ADC_11db: sets an attenuation of 3.6 (1V input = ADC reading of 3959).
  https://www.esp32.com/viewtopic.php?f=19&t=2881&start=10#p13739
--------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------

Stable time: ~25 second.
*/
#ifndef  __ESP32_ADC_CPP 
#define  __ESP32_ADC_CPP
#include "ESP32_ADC.h"

// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------
/**
Read value of the ADC 
**/
int ADC_read(int,int,int);
// ------ Private variables -----------------------------------
SimpleKalmanFilter filter(E_MEA, E_EST, Q); //For flow sensors, we don't have one so we cannot test it
SimpleKalmanFilter filter1(E_MEA, E_EST, Q); //For T1
SimpleKalmanFilter filter2(E_MEA, E_EST, Q); //For T2
SimpleKalmanFilter filter3(E_MEA, E_EST, Q); //For T3
SimpleKalmanFilter filter4(E_MEA, E_EST, Q); //For T4
// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void ADC_init() 
{
  analogReadResolution(11); // Default of 12 is not very linear. Recommended to use 10 or 11 depending on needed resolution.
  analogSetWidth(11); //Range 0-2047
  analogSetPinAttenuation(TEMP_SEN01_PIN, ADC_6db); // Default is 11db which is very noisy. Recommended to use 2.5 or 6.
  analogSetPinAttenuation(TEMP_SEN02_PIN, ADC_6db); // Default is 11db which is very noisy. Recommended to use 2.5 or 6.
  analogSetPinAttenuation(TEMP_SEN03_PIN, ADC_6db); // Default is 11db which is very noisy. Recommended to use 2.5 or 6.
  analogSetPinAttenuation(TEMP_SEN04_PIN, ADC_6db); // Default is 11db which is very noisy. Recommended to use 2.5 or 6.
  analogSetPinAttenuation(FLOW_SEN01_PIN, ADC_11db); // Must use 11db because of the module MDCB042
  analogSetPinAttenuation(FLOW_SEN02_PIN, ADC_11db); // Must use 11db because of the module MDCB042
  //analogSetAttenuation(ADC_6db); // This can be used for all ADC pins, but not recommended.
}//end ADC_init
//------------------------------------------
int ADC_read(int ADCpin, int lowVal, int maxVal)
{
  // read the input on the corresponding analog pin:
  //if recieved signal is less than 4mA, than the sensor is off or is having some errors
  //if recieved signal is equal or more than 4mA (~360mV ~398 ADC value), than the sensor is working probaly
  int senVal = analogRead(ADCpin);
  //------------------------------Kalman filter applied:
  int es_senVal = filter.updateEstimate(senVal); // first layer
  for (int a=1;a<FILTER_LAYER; a++) {        // next layers (if possible)
    es_senVal = filter.updateEstimate(es_senVal);   
  }//end for
  //------------------------------Kalman filter done
  if (es_senVal<200) //if sensor is off or error
    {return SENSOR_ERROR;} //use 200 for compensating for noises.
  int calculatedVal = map(es_senVal,398,2047,lowVal,maxVal); //map es_senVal from 0-2047 to lowVal-maxVal
  return calculatedVal; //return the calculated value
}//end ADC_read
//------------------------------------------
int flowSen01_read() {
  return ADC_read(FLOW_SEN01_PIN,FLOW_MIN,FLOW_MAX);
}//end flowSen01_read
//------------------------------------------
int flowSen02_read() {
  return ADC_read(FLOW_SEN02_PIN,FLOW_MIN,FLOW_MAX);
}//end flowSen02_read
//------------------------------------------
int tempSen01_read() {
   int a1 = analogRead(TEMP_SEN01_PIN);
  //------------------------------Kalman filter applied:
  int es_senVal1 = filter1.updateEstimate(a1); // first layer
  for (int a=1;a<FILTER_LAYER; a++) {        // next layers (if possible)
    int es_senVal1 = filter1.updateEstimate(es_senVal1);   
  }//end for
  //------------------------------Kalman filter done
  int t1= map(es_senVal1,398,2047,lowVal,maxVal);   
  return t1;
}//end tempSen01_read
//------------------------------------------
int tempSen02_read() {
   int a2 = analogRead(TEMP_SEN02_PIN);
  //------------------------------Kalman filter applied:
  int es_senVal2 = filter2.updateEstimate(a2); // first layer
  for (int a=1;a<FILTER_LAYER; a++) {        // next layers (if possible)
    es_senVal2 = filter2.updateEstimate(es_senVal2);   
  }//end for
  //------------------------------Kalman filter done
  int t2=map(es_senVal2,398,2047,lowVal,maxVal); 
  return t2;
}//end tempSen02_read
//------------------------------------------
int tempSen03_read() {
   int a3 = analogRead(TEMP_SEN03_PIN);
  //------------------------------Kalman filter applied:
  int es_senVal3 = filter3.updateEstimate(a3); // first layer
  for (int a=1;a<FILTER_LAYER; a++) {        // next layers (if possible)
    es_senVal3 = filter3.updateEstimate(es_senVal3);   
  }//end for
  //------------------------------Kalman filter done
  int t3=map(es_senVal3,398,2047,lowVal,maxVal); 
  return t3;
}//end tempSen03_read
//------------------------------------------
int tempSen04_read() {
   int a4 = analogRead(TEMP_SEN04_PIN);
  //------------------------------Kalman filter applied:
  int es_senVal4 = filter4.updateEstimate(a4); // first layer
  for (int a=1;a<FILTER_LAYER; a++) {        // next layers (if possible)
    es_senVal4 = filter4.updateEstimate(es_senVal4);   
  }//end for
  int t4=map(es_senVal4,398,2047,lowVal,maxVal); 
  return t4;
}//end tempSen04_read
//------------------------------------------
#endif //__ESP32_ADC_CPP
