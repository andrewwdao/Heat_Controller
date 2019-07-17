
#include "config.h"

volatile int pwm_valueP1 = 0;
volatile int prev_timeP1 = 0;
volatile int pwm_freqP1  = 0;
volatile bool gotFreqPump1 = false;
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
  ledcWrite(PWM_CHANNEL_1, MAX_SPEED);
}
//end pump1_maxspeed
void pump1_minspeed() {
  ledcWrite(PWM_CHANNEL_1, MIN_SPEED );
}
//------------------
void pump1_varmaxspeed() {
  ledcWrite(PWM_CHANNEL_1, VAR_MAXSPEED  );
}
//------------------
void pump1_varminspeed() {
  ledcWrite(PWM_CHANNEL_1, VAR_MINSPEED  );
}
//------------------
void pump1_HYSTERESISspeed() {
  ledcWrite(PWM_CHANNEL_1, HYSTERESIS_ON_OFF   );
}
//------------------
void pump1_STANDBY_MODE_OFFspeed() {
  ledcWrite(PWM_CHANNEL_1,STANDBY_MODE_OFF);
}
//------------------------
void pump2_maxspeed() {
  ledcWrite(PWM_CHANNEL_2, MAX_SPEED);
}
//end pump1_maxspeed
void pump2_minspeed() {
  ledcWrite(PWM_CHANNEL_2, MIN_SPEED );
}
//------------------
void pump2_varmaxspeed() {
  ledcWrite(PWM_CHANNEL_2, VAR_MAXSPEED  );
}
//------------------
void pump2_varminspeed() {
  ledcWrite(PWM_CHANNEL_2, VAR_MINSPEED  );
}
//------------------
void pump2_HYSTERESISspeed() {
  ledcWrite(PWM_CHANNEL_2, HYSTERESIS_ON_OFF   );
}
//------------------
void pump2_STANDBY_MODE_OFFspeed() {
  ledcWrite(PWM_CHANNEL_2,STANDBY_MODE_OFF);
}
//------------------------
void setup(){
  Serial.begin(115200);
 pump2_init();
 // pump1_init();
//  pump1_maxspeed();
//pump1_minspeed() ;
//pump1_varmaxspeed();
//pump1_varminspeed() ;
//pump1_HYSTERESISspeed();
//pump1_STANDBY_MODE_OFFspeed();
//pump2_maxspeed();
//pump2_minspeed() ;
//pump2_varmaxspeed();
//pump2_varminspeed() ;
//pump2_HYSTERESISspeed();
pump2_STANDBY_MODE_OFFspeed();

}

void loop()
{
  S_PRINTLN("Hello");
  delay(1000);
}
