/*-------------------------------------------------------------
  ADC Converter - header file
  ESP32 DEVKIT V1
  (c) An Minh Dao - 2019 
  version 1.00 - 14/08/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#ifndef __ESP32_ADC_H
#define __ESP32_ADC_H
#include <WiFi.h> //for esp32
#include <driver/adc.h>
#include <SimpleKalmanFilter.h>
//#include "config.h"

// ------ Public constants ------------------------------------
//--------------------------------------------------------------
// FLOW MAPPING
//--------------------------------------------------------------
#define FLOW_MIN 0    //put the mininum value of your flow sensor here
#define FLOW_MAX 100  //put the maximum value of your flow sensor here
//--------------------------------------------------------------
// TEMPERATURE MAPPING
//--------------------------------------------------------------
#define TEMP_MIN 0    //put the mininum value of your temperature sensor here
#define TEMP_MAX 850  //put the maximum value of your temperature sensor here
//--------------------------------------------------------------
// ADC
//--------------------------------------------------------------
#define FLOW_SEN01_PIN 36
#define FLOW_SEN02_PIN 39
#define TEMP_SEN01_PIN 34
#define TEMP_SEN02_PIN 35
#define TEMP_SEN03_PIN 32
#define TEMP_SEN04_PIN 33
#define SENSOR_ERROR   9999
//KALMAN FILTER PARAMETERS
#define FILTER_LAYER 2
#define E_MEA 3     //Measurement Uncertainty - How much do we expect to our measurement vary
#define E_EST 3     //Estimation Uncertainty - Can be initilized with the same value as e_mea since the kalman filter will adjust its value.
#define Q     0.007 //Process Variance - usually a small number between 0.001 and 1 - how fast your measurement moves. Recommended 0.01. Should be tunned to your needs.
// ------ Public function prototypes --------------------------
/**
Initialize ADC
**/
void ADC_init();
/**
Read value of the flow Sensor 01
**/
int flowSen01_read();
/**
Read value of the flow Sensor 02
**/
int flowSen02_read();
/**
Read value of the temperature Sensor 01
**/
int tempSen01_read();
/**
Read value of the temperature Sensor 02
**/
int tempSen02_read();
/**
Read value of the temperature Sensor 03
**/
int tempSen03_read();
/**
Read value of the temperature Sensor 04
**/
int tempSen04_read();
// ------ Public variable -------------------------------------

#endif // __ESP32_ADC_H
