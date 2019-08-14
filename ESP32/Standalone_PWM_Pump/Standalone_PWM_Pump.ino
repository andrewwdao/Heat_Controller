
#include "config.h"
int pump1_output = OFF_MODE;
volatile uint32_t p1_pulseLength=0;
volatile float    p1_dutyCycle = 0;
uint32_t p1Millis=0;
int pump2_output = OFF_MODE;
volatile uint32_t p2_pulseLength=0;
volatile float    p2_dutyCycle = 0;
uint32_t p2Millis=0;

uint32_t Millis=0;

void pump1_init() {
  //output pwm to pump
  ledcSetup(PWM_CHANNEL_1, PWM_FREQ, PWM_RES); // configure PWM chanel corresponding to frequency and resolution
  ledcAttachPin(PUMP1_OUT_PIN, PWM_CHANNEL_1);// attach the channel to the GPIO to be controlled
  //input pwm from pump
  pinMode(PUMP1_IN_PIN, INPUT);
}//end pump1_init

void pump2_init() {
  //output pwm to pump
  ledcSetup(PWM_CHANNEL_2, PWM_FREQ, PWM_RES); // configure PWM chanel corresponding to frequency and resolution
  ledcAttachPin(PUMP2_OUT_PIN, PWM_CHANNEL_2);// attach the channel to the GPIO to be controlled
  //input pwm from pump
  pinMode(PUMP2_IN_PIN, INPUT);
}//end pump2_init

void pump1_maxspeed() {
  pump1_output = VAR_MAXSPEED; //set normal output to pseudo maximum value in case of pump_faster() function is called.
  ledcWrite(PWM_CHANNEL_1, MAX_SPEED); //put the pump in the real maximum speed
}//end pump1_maxspeed
void pump1_minspeed() {
  pump1_output = VAR_MINSPEED; //set normal output to pseudo maximum value in case of pump_slower() function is called.
  ledcWrite(PWM_CHANNEL_1, MIN_SPEED); //put the pump in the real minimum speed
}//end pump1_minspeed
void pump1_faster(int valPump) { //valPump goes from 0.01 to 1 (1% to 100%)
  pump1_output += (pump1_output>=(VAR_MAXSPEED-1))?(0):(valPump)*PWM_RESOLUTION; //plus 1% of duty cycle each time this function is called if maximum value is not exceeded.
  ledcWrite(PWM_CHANNEL_1, pump1_output); //output signal to the pump
}//end pump1_faster
void pump1_slower(int valPump) {//valPump goes from 0.01 to 1 (1% to 100%)
  pump1_output -= (pump1_output<=(VAR_MINSPEED+1))?(0):(valPump)*PWM_RESOLUTION; //plus 1% of duty cycle each time this function is called if maximum value is not exceeded.
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
    p1_pulseLength = pulseIn(PUMP1_IN_PIN, LOW, 15000);//Pin, start to count when catch a high pulse, wait for 15ms before return 0 (75Hz~13,33ms)
    S_PRINTLN(p1_pulseLength);
    p1_dutyCycle = ((float)p1_pulseLength/(float)PUMP_CYCLE);
    S_PRINTLN(p1_dutyCycle);
    if (p1_dutyCycle>PUMP_STANDBY) {S_PRINTLN(F("pump1 Standby!"));return;}
    if (p1_dutyCycle>PUMP_BLOCK_ERROR) {S_PRINTLN(F("pump1 Error! Pump Blocked"));return;}
    if (p1_dutyCycle>PUMP_ELECTRICAL_ERROR) {S_PRINTLN(F("pump1 Error! Electrical error!"));return;}
    if (p1_dutyCycle>PUMP_WARNING) {S_PRINTLN(F("Pump 1 Warning!"));return;}
    if (p1_dutyCycle==0) {S_PRINTLN(F("pump1 No signal!"));return;}
    if (p1_dutyCycle<PUMP_NORMAL) {S_PRINTLN(F("Pump2 in normal condition!"));return;}
}//end pump1_status

void pump2_status() {
    p2_pulseLength = pulseIn(PUMP2_IN_PIN, LOW, 15000);//Pin, start to count when catch a high pulse, wait for 15ms before return 0 (75Hz~13,33ms)
    S_PRINTLN(p2_pulseLength);
    p2_dutyCycle = ((float)p2_pulseLength/(float)PUMP_CYCLE);
    S_PRINTLN(p2_dutyCycle);
    if (p2_dutyCycle>PUMP_STANDBY) {S_PRINTLN(F("pump2 Standby!"));return;}
    if (p2_dutyCycle>PUMP_BLOCK_ERROR) {S_PRINTLN(F("pump2 Error! Pump Blocked"));return;}
    if (p2_dutyCycle>PUMP_ELECTRICAL_ERROR) {S_PRINTLN(F("pump2 Error! Electrical error!"));return;}
    if (p2_dutyCycle>PUMP_WARNING) {S_PRINTLN(F("Pump 2 Warning!"));return;}
    if (p2_dutyCycle==0) {S_PRINTLN(F("pump2 No signal!"));return;}
    if (p2_dutyCycle<PUMP_NORMAL) {S_PRINTLN(F("Pump2 in normal condition!"));return;}
}//end pump1_status
void setup(){
  Serial.begin(115200);
  Millis = millis();
  pump1_init();
  pump2_init();
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
  
  if ((millis()-Millis)>1000) {
    Millis=millis();
    //pump2_status();
    pump1_status();
  }
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
