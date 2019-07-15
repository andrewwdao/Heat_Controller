/*
  AnalogRead Serial
  https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
  ADC_0db: sets no attenuation (1V input = ADC reading of 1088).
  ADC_2_5db: sets an attenuation of 1.34 (1V input = ADC reading of 2086).
  ADC_6db: sets an attenuation of 1.5 (1V input = ADC reading of 2975).
  ADC_11db: sets an attenuation of 3.6 (1V input = ADC reading of 3959).
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

int ADC_read(int ADCpin)
{
  // read the input on the corresponding analog pin:
  int senVal = analogRead(ADCpin);
  int es_senVal = filter.updateEstimate(senVal); // first layer
  for (int a=0;a<FILTER_LAYER; a++) {        // next layers (if possible)
    es_senVal = filter.updateEstimate(es_senVal);   
  }//end for
  return es_senVal; //return the calculated value
}//end ADC_read

int flowSen01_read() {
  return ADC_read(36);
}//end flowSen01_read

int flowSen02_read() {
  return ADC_read(39);
}//end flowSen02_read

int tempSen01_read() {
  return ADC_read(34);
}//end tempSen01_read

int tempSen02_read() {
  return ADC_read(35);
}//end tempSen02_read

int tempSen03_read() {
  return ADC_read(32);
}//end tempSen03_read

int tempSen04_read() {
  return ADC_read(33);
}//end tempSen04_read
void setup() {
  Serial.begin(115200);// initialize serial communication at 115200 bits per second
  ADC_init();
}

void loop() { //forever loop
  // print out the value you read:
  Serial.println(flowSen02_read());
  delay(100);        // delay in between reads for stability
}
