/*
  AnalogRead Serial
  https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
  ADC_0db: sets no attenuation (1V input = ADC reading of 1088).
  ADC_2_5db: sets an attenuation of 1.34 (1V input = ADC reading of 2086).
  ADC_6db: sets an attenuation of 1.5 (1V input = ADC reading of 2975).
  ADC_11db: sets an attenuation of 3.6 (1V input = ADC reading of 3959).

Stable time: ~60 second.
*/
#include "config.h"
SimpleKalmanFilter filter(E_MEA, E_EST, Q);

void ADC_init() 
{
  analogReadResolution(11); // Default of 12 is not very linear. Recommended to use 10 or 11 depending on needed resolution.
  analogSetWidth(11); //Range 0-2047
  analogSetAttenuation(ADC_6db); // Default is 11db which is very noisy. Recommended to use 2.5 or 6.
  //analogSetPinAttenuation(ADC1_0, ADC_6db);
}//end ADC_init

int ADC_read(int ADCpin, int lowVal, int maxVal)
{
  // read the input on the corresponding analog pin:
  //if recieved signal is less than 4mA, than the sensor is off or is having some errors
  //if recieved signal is equal or more than 4mA (~360mV ~398 ADC value), than the sensor is working probaly
  int senVal = analogRead(ADCpin);
  //------------------------------Kalman filter applied:
  int es_senVal = filter.updateEstimate(senVal); // first layer
  for (int a=0;a<FILTER_LAYER; a++) {        // next layers (if possible)
    es_senVal = filter.updateEstimate(es_senVal);   
  }//end for
  //------------------------------Kalman filter done
  if (es_senVal<200) //if sensor is off or error
    {return SENSOR_ERROR;} //use 200 for compensating for noises.
  int calculatedVal = map(es_senVal,398,2047,lowVal,maxVal); //map es_senVal from 0-2047 to lowVal-maxVal
  return calculatedVal; //return the calculated value
}//end ADC_read

int flowSen01_read() {
  return ADC_read(FLOW_SEN01_PIN,FLOW_MIN,FLOW_MAX);
}//end flowSen01_read

int flowSen02_read() {
  return ADC_read(FLOW_SEN02_PIN,FLOW_MIN,FLOW_MAX);
}//end flowSen02_read

int tempSen01_read() {
  return ADC_read(TEMP_SEN01_PIN,TEMP_MIN,TEMP_MAX);
}//end tempSen01_read

int tempSen02_read() {
  return ADC_read(TEMP_SEN02_PIN,TEMP_MIN,TEMP_MAX);
}//end tempSen02_read

int tempSen03_read() {
  return ADC_read(TEMP_SEN03_PIN,TEMP_MIN,TEMP_MAX);
}//end tempSen03_read

int tempSen04_read() {
  return ADC_read(TEMP_SEN04_PIN,TEMP_MIN,TEMP_MAX);
}//end tempSen04_read
void setup() {
  Serial.begin(115200);// initialize serial communication at 115200 bits per second
  ADC_init();
}

void loop() { //forever loop
//print out the value you read:
//  Serial.println(flowSen01_read());
//  Serial.println(flowSen02_read());
//  Serial.println(tempSen01_read());
//  Serial.println(tempSen02_read());
//  Serial.println(tempSen03_read());
  Serial.println(tempSen04_read());
  delay(100);        // delay in between reads for stability
}
