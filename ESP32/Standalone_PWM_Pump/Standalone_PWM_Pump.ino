
#include "config.h"
int pump1_output = OFF_MODE;
volatile uint32_t rise_timeP1 = 0;
volatile uint32_t fall_timeP1 = 0;
volatile float    p1_dutyCycle = 0;
volatile bool gotResPump1 = false;
uint32_t p1Millis=0;
int pump2_output = OFF_MODE;
volatile uint32_t prev_timeP2 = 0;
volatile uint32_t pwm_valueP2 = 0;
volatile float    p2_dutyCycle = 0;
volatile bool gotResPump2 = false;
uint32_t p2Millis=0;

uint32_t Millis=0;

//void pump01_rise_ISR() {
//  attachInterrupt(PUMP1_IN_PIN, pump01_fall_ISR, FALLING);
//  rise_timeP1 = micros();
//}//end PWM_pump01_rise
//
//void pump01_fall_ISR() {
//  attachInterrupt(PUMP1_IN_PIN, pump01_rise_ISR, RISING);
//  fall_timeP1 = micros();
//  gotResPump1 = true;
//}//end PWM_pump01_fall
//
//void pump02_rise_ISR() {
//  attachInterrupt(PUMP2_IN_PIN, pump02_fall_ISR, FALLING);
//  //prev_timeP2 = xTaskGetTickCountFromISR(); //micros();
//}//end PWM_pump02_rise
//
//void pump02_fall_ISR() {
//  attachInterrupt(PUMP2_IN_PIN, pump02_rise_ISR, RISING);
//  //p2_dutyCycle = (float)((xTaskGetTickCountFromISR()-prev_timeP2)/PUMP_CYCLE);
//  gotResPump2 = true;
//}//end PWM_pump02_fall

void pump1_init() {
  //output pwm to pump
  ledcSetup(PWM_CHANNEL_1, PWM_FREQ, PWM_RES); // configure PWM chanel corresponding to frequency and resolution
  ledcAttachPin(PUMP1_OUT_PIN, PWM_CHANNEL_1);// attach the channel to the GPIO to be controlled
  //input pwm from pump
  pinMode(PUMP1_IN_PIN, INPUT_PULLUP);
//  attachInterrupt(PUMP1_IN_PIN, pump01_rise_ISR, RISING);
//  gotResPump1 = false;
//  p1Millis=millis();
}//end pump1_init

void pump2_init() {
  //output pwm to pump
  ledcSetup(PWM_CHANNEL_2, PWM_FREQ, PWM_RES); // configure PWM chanel corresponding to frequency and resolution
  ledcAttachPin(PUMP2_OUT_PIN, PWM_CHANNEL_2);// attach the channel to the GPIO to be controlled
  //input pwm from pump
  pinMode(PUMP2_IN_PIN, INPUT_PULLUP);
//  attachInterrupt(PUMP2_IN_PIN, pump02_rise_ISR, RISING);
//  gotResPump2 = false;
//  p2Millis=millis();
}//end pump2_init

void pump1_maxspeed() {
  pump1_output = VAR_MAXSPEED; //set normal output to pseudo maximum value in case of pump_faster() function is called.
  ledcWrite(PWM_CHANNEL_1, MAX_SPEED); //put the pump in the real maximum speed
}//end pump1_maxspeed
void pump1_minspeed() {
  pump1_output = VAR_MINSPEED; //set normal output to pseudo maximum value in case of pump_slower() function is called.
  ledcWrite(PWM_CHANNEL_1, MIN_SPEED); //put the pump in the real minimum speed
}//end pump1_minspeed
void pump1_faster() {
  pump1_output += (pump1_output>=(VAR_MAXSPEED-1))?(0):(0.01)*PWM_RESOLUTION; //plus 1% of duty cycle each time this function is called if maximum value is not exceeded.
  ledcWrite(PWM_CHANNEL_1, pump1_output); //output signal to the pump
}//end pump1_faster
void pump1_slower() {
  pump1_output -= (pump1_output<=(VAR_MINSPEED+1))?(0):(0.01)*PWM_RESOLUTION; //plus 1% of duty cycle each time this function is called if maximum value is not exceeded.
  ledcWrite(PWM_CHANNEL_1, pump1_output); //output signal to the pump
}//end pump1_slower
void pump1_OFF() {
  ledcWrite(PWM_CHANNEL_1,OFF_MODE);
}//end pump1_OFF
//-----------------------------------------------------
void pump2_maxspeed() {
  pump2_output = VAR_MAXSPEED; //set normal output to pseudo maximum value in case of pump_faster() function is called.
  ledcWrite(PWM_CHANNEL_2, MAX_SPEED); //put the pump in the real maximum speed
}//end pump1_maxspeed
void pump2_minspeed() {
  pump2_output = VAR_MINSPEED; //set normal output to pseudo maximum value in case of pump_slower() function is called.
  ledcWrite(PWM_CHANNEL_2, MIN_SPEED); //put the pump in the real minimum speed
}//end pump1_minspeed
void pump2_faster() {
  pump2_output += (pump2_output>=(VAR_MAXSPEED-1))?(0):(0.01)*PWM_RESOLUTION; //plus 1% of duty cycle each time this function is called if maximum value is not exceeded.
  ledcWrite(PWM_CHANNEL_2, pump2_output); //output signal to the pump
}//end pump1_faster
void pump2_slower() {
  pump2_output -= (pump2_output<=(VAR_MINSPEED+1))?(0):(0.01)*PWM_RESOLUTION; //plus 1% of duty cycle each time this function is called if maximum value is not exceeded.
  ledcWrite(PWM_CHANNEL_2, pump2_output); //output signal to the pump
}//end pump1_slower
void pump2_OFF() {
  ledcWrite(PWM_CHANNEL_2,OFF_MODE);
}//end pump1_OFF
//------------------------
void pump1_status() {
  if ((gotResPump1)&&((millis()-p1Millis)>1000)) {
    
    gotResPump1 = false;
    p1_dutyCycle = (float)((fall_timeP1-rise_timeP1)/PUMP_CYCLE);
    S_PRINTLN(rise_timeP1);
    S_PRINTLN(fall_timeP1);
    S_PRINTLN(p1_dutyCycle);
    p1Millis = millis();
    if (p1_dutyCycle>PUMP_STANDBY) {S_PRINTLN(F("Stand by!"));return;}
    if (p1_dutyCycle>PUMP_BLOCK_ERROR) {S_PRINTLN(F("Error! Pump Blocked"));return;}
    if (p1_dutyCycle>PUMP_ELECTRICAL_ERROR) {S_PRINTLN(F("Error! Electrical error!"));return;}
    if (p1_dutyCycle>PUMP_WARNING) {S_PRINTLN(F("Pump Warning!"));return;}
    if (p1_dutyCycle<PUMP_NORMAL) {S_PRINTLN(F("Pump in normal condition!"));return;}
  }//end if
}//end pump1_status

void setup(){
  Serial.begin(115200);
  Millis = millis();
  pump1_init();
// pump2_init();
// pump1_maxspeed();
//pump1_minspeed() ;

//pump1_faster();
//pump1_slower();
//  pump1_OFF();

  
// pump2_maxspeed();
//pump2_minspeed() ;
//pump2_faster();
//  pump2_slower();
//  pump2_OFF();

}

void loop()
{
  pump1_status();
//  if ((millis()-Millis)>1000) {
//   // pump1_slower();
// //pump2_faster();
//   pump1_faster();
//  //  pump2_slower();
//  delay(1000);
//  pump1_slower();
//     Millis=millis();
//    S_PRINTLN("Hello2");
//  }

}
