/*-------------------------------------------
  UART - functions file
  ESP32 DEVKIT V1
  (c) An Minh Dao - Pham Thanh Tam 2019 
  version 1.10 - 26/08/2019
--------------------------------------------*/ 
#ifndef  __ESP32_UART_CPP
#define  __ESP32_UART_CPP
#include "ESP32_UART.h"

// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------
/**

**/
//void sendSD(int,int,int,int,int,int);
// ------ Private variables -----------------------------------

// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
void UART_init()
{
  Serial.begin(57600);
}
//------------------------------------------------------------
void UART_masterReady() {
  Serial.print('k');
  Serial.print(AUTHORIZED_KEY);
}//end UART_masterReady
//------------------------------------------------------------
 void UART_sendToSlave() {//command: t|T1|T2|T3|T4_f|F1|F2
  char Smes[60];
  snprintf(Smes,60,"t|%d|%d|%d|%d_f|%d|%d",tempSen01_read(),tempSen02_read(),tempSen03_read(),tempSen04_read(),flowSen01_read(),flowSen02_read());
  Serial.println(Smes);
}// end UART_sendToSlave
void UART_getFromSlave() {// p|Kp|Ki|Kd or t|T1|T2|T3|T4 or f|F1|F2
  if( Serial.available()) {//if something appear in the serial monitor
    char charBuf = Serial.read();
    if (charBuf=='p') {
      uint16_t p1,p2,p3;
      float fKp,fKi,fKd;
      String bKp="",bKi="",bKd="",rec="";
      rec=Serial.readString();
      p1=rec.indexOf("|",0); //search for initial signal
      if (p1>=0) { //has the correct signal
        //pid parameters
        p1=rec.indexOf("|",0);    //position of temp1
        p2=rec.indexOf("|",p1+1); //position of temp2
        p3=rec.indexOf("|",p2+1); //position of temp3
        bKp=rec.substring(p1+1,p2);//get the string out
        bKi=rec.substring(p2+1,p3);//get the string out
        bKd=rec.substring(p3+1);//get the string out
        fKp=bKp.toFloat(); //temp1
        fKi=bKi.toFloat(); //temp2
        fKd=bKd.toFloat(); //temp3
        Serial.println(fKp);
        Serial.println(fKi);
        Serial.println(fKd);
      } else {
         D_PRINTLN(F("Not recognized command!"));
      }// end if else
    } else if (charBuf=='t') {
      uint16_t t1,t2,t3,t4;
      int fT1,fT2,fT3,fT4;
      String bT1="",bT2="",bT3="",bT4="",rec="";
      rec=Serial.readString();
      t1=rec.indexOf("|",0); //search for initial signal
      if (t1>=0) { //has the correct signal
        //set temperature values
        t1=rec.indexOf("|",0);    //position of temp1
        t2=rec.indexOf("|",t1+1); //position of temp2
        t3=rec.indexOf("|",t2+1); //position of temp3
        t4=rec.indexOf("|",t3+1); //position of temp4
        bT1=rec.substring(t1+1,t2);//get the string out
        bT2=rec.substring(t2+1,t3);//get the string out
        bT3=rec.substring(t3+1,t4);//get the string out
        bT4=rec.substring(t4+1);   //get the string out
        fT1=bT1.toInt(); //temp1
        fT2=bT2.toInt(); //temp2
        fT3=bT3.toInt(); //temp3
        fT4=bT4.toInt(); //temp4
        Serial.println(fT1);
        Serial.println(fT2);
        Serial.println(fT3);
        Serial.println(fT4);
      } else {
         D_PRINTLN(F("Not recognized command!"));
      }// end if else
    } else if (charBuf=='f') {
      uint16_t f1,f2;
      int fF1,fF2;
      String bF1="",bF2="", rec="";
      rec=Serial.readString();
      f1=rec.indexOf("|",0); //search for initial signal
      if (f1>=0) { //has the correct signal
        //set flow values
        f1=rec.indexOf("|",0);    //position of temp1
        f2=rec.indexOf("|",f1+1); //position of temp2
        bF1=rec.substring(f1+1,f2);//get the string out
        bF2=rec.substring(f2+1);//get the string out
        fF1=bF1.toInt(); //flow1
        fF2=bF2.toInt(); //flow2
        Serial.println(fF1);
        Serial.println(fF2);
      } else {
         D_PRINTLN(F("Not recognized command!"));
      }// end if else 
    } else {
      D_PRINTLN(F("Not recognized command!"));
    }// end if else
  }//end if
}//end UART_getFromSlave
//--------------------------------
#endif // __ESP32_UART_CPP
