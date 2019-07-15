/*
  AnalogRead Serial
  https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
  ADC_0db: sets no attenuation (1V input = ADC reading of 1088).
  ADC_2_5db: sets an attenuation of 1.34 (1V input = ADC reading of 2086).
  ADC_6db: sets an attenuation of 1.5 (1V input = ADC reading of 2975).
  ADC_11db: sets an attenuation of 3.6 (1V input = ADC reading of 3959).
*/
#include <driver/adc.h>
#include <SimpleKalmanFilter.h>
SimpleKalmanFilter filter(2, 2, 0.01);
float es_senVal=0;
void setup() {
  Serial.begin(115200);// initialize serial communication at 115200 bits per second
  analogReadResolution(11); // Default of 12 is not very linear. Recommended to use 10 or 11 depending on needed resolution.
  analogSetWidth(11); //Range 0-2047
  analogSetAttenuation(ADC_6db); // Default is 11db which is very noisy. Recommended to use 2.5 or 6.
  //analogSetPinAttenuation(ADC1_0, ADC_6db);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog ADC1_0 (VP pin):
  int senVal = analogRead(34);
  es_senVal = filter.updateEstimate(senVal); // 1 layer
  for (int a=0;a<4; a++) {
    es_senVal = filter.updateEstimate(es_senVal); // 2 layer  
  }//end for
  // print out the value you read:
  Serial.println(es_senVal);
  delay(100);        // delay in between reads for stability
}
