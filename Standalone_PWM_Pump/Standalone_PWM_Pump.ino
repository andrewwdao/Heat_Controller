
#include "config.h"
int pump1_output = OFF_MODE;
volatile int pwm_valueP1 = 0;
volatile int prev_timeP1 = 0;
volatile int pwm_freqP1  = 0;
volatile bool gotFreqPump1 = false;
int pump2_output = OFF_MODE;
volatile int pwm_valueP2 = 0;
volatile int prev_timeP2 = 0;
volatile int pwm_freqP2  = 0;
volatile bool gotFreqPump2 = false;

void pump01_fall_ISR() {
  attachInterrupt(PUMP1_IN_PIN, pump01_rise_ISR, RISING);
  pwm_valueP1 = (micros()-prev_timeP1)/1000000;
  pwm_freqP1  = (pwm_valueP1)?(1/pwm_valueP1):(NO_PWM_INPUT);
  gotFreqPump1 = true;
}//end PWM_pump01_fall

void pump01_rise_ISR() {
  attachInterrupt(PUMP1_IN_PIN, pump01_fall_ISR, FALLING);
  prev_timeP1 = micros();
  gotFreqPump1 = false;
}//end PWM_pump01_rise
 
void pump02_fall_ISR() {
  attachInterrupt(PUMP2_IN_PIN, pump02_rise_ISR, RISING);
  pwm_valueP2 = (micros()-prev_timeP2)/1000000;
  pwm_freqP2  = (pwm_valueP2)?(1/pwm_valueP2):(NO_PWM_INPUT);
  gotFreqPump2 = true;
}//end PWM_pump02_fall

void pump02_rise_ISR() {
  attachInterrupt(PUMP2_IN_PIN, pump02_fall_ISR, FALLING);
  prev_timeP2 = micros();
  gotFreqPump2 = false;
}//end PWM_pump02_rise

void pump1_init() {
  //output pwm to pump
  ledcSetup(PWM_CHANNEL_1, PWM_FREQ, PWM_RES); // configure PWM chanel corresponding to frequency and resolution
  ledcAttachPin(PUMP1_OUT_PIN, PWM_CHANNEL_1);// attach the channel to the GPIO to be controlled
  //input pwm from pump
  pinMode(PUMP1_IN_PIN, INPUT);
  attachInterrupt(PUMP1_IN_PIN, pump01_rise_ISR, RISING);
  gotFreqPump1 = false;
}//end pump1_init

void pump2_init() {
  //output pwm to pump
  ledcSetup(PWM_CHANNEL_2, PWM_FREQ, PWM_RES); // configure PWM chanel corresponding to frequency and resolution
  ledcAttachPin(PUMP2_OUT_PIN, PWM_CHANNEL_2);// attach the channel to the GPIO to be controlled
  //input pwm from pump
  pinMode(PUMP2_IN_PIN, INPUT);
  attachInterrupt(PUMP2_IN_PIN, pump02_rise_ISR, RISING);
  gotFreqPump2 = false;
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
  pump1_output += (pump1_output==VAR_MAXSPEED)?(0):(0.01); //plus 1% of duty cycle each time this function is called if maximum value is not exceeded.
  ledcWrite(PWM_CHANNEL_1, pump1_output); //output signal to the pump
}//end pump1_faster
void pump1_slower() {
  pump1_output -= (pump1_output==VAR_MINSPEED)?(0):(0.01); //plus 1% of duty cycle each time this function is called if maximum value is not exceeded.
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
  pump2_output += (pump2_output==VAR_MAXSPEED)?(0):(0.01); //plus 1% of duty cycle each time this function is called if maximum value is not exceeded.
  ledcWrite(PWM_CHANNEL_2, pump2_output); //output signal to the pump
}//end pump1_faster
void pump2_slower() {
  pump2_output -= (pump2_output==VAR_MINSPEED)?(0):(0.01); //plus 1% of duty cycle each time this function is called if maximum value is not exceeded.
  ledcWrite(PWM_CHANNEL_2, pump2_output); //output signal to the pump
}//end pump1_slower
void pump2_OFF() {
  ledcWrite(PWM_CHANNEL_2,OFF_MODE);
}//end pump1_OFF
//------------------------
void setup(){
  Serial.begin(115200);

  pump1_init();
  pump1_maxspeed();
//  pump1_minspeed() ;
//  pump1_faster();
//  pump1_slower();
//  pump1_OFF();

  pump2_init();
  pump2_maxspeed();
//  pump2_minspeed() ;
//  pump2_faster();
//  pump2_slower();
//  pump2_OFF();

}

void loop()
{
  S_PRINTLN("Hello");
  delay(1000);
}
