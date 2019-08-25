/*-------------------------------------------
  UART - header file
  ARDUINO NANO
  (c) An Minh Dao - Pham Thanh Tam 2019 
  version 1.10 - 25/08/2019
--------------------------------------------*/ 
#ifndef  __NANO_UART_CPP
#define  __NANO_UART_CPP
#include "Nano_UART.h"

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
  Serial.begin(115200);
}
//------------------------------------------------------------
 void getFromMaster() //command: t|T1|T2|T3|T4_f|F1|F2
{
  if( Serial.available()) //if something appear in the serial monitor
  { 
    int t1,t2,t3,t4,f1,f2;
    String buff1="",buff2="",buff3="",buff4="",rec="";
    rec=Serial.readString();
    t1=rec.indexOf("t",0); //search for initial signal - t for temperature
    f1=rec.indexOf("f",0); //search for initial signal - f for flow
    if((t1>=0)&&(f1>=0)) // if exist signal "t" and "f"
    {
      //temperature
      t1=rec.indexOf("|",0);    //position of temp1
      t2=rec.indexOf("|",t1+1); //position of temp2
      t3=rec.indexOf("|",t2+1); //position of temp3
      t4=rec.indexOf("|",t3+1); //position of temp4
      buff1=rec.substring(t1+1,t2);//get the string out
      buff2=rec.substring(t2+1,t3);//get the string out
      buff3=rec.substring(t3+1,t4);//get the string out
      buff4=rec.substring(t4+1);   //get the string out
      t1=buff1.toInt(); //temp1
      t2=buff2.toInt(); //temp2
      t3=buff3.toInt(); //temp3
      t4=buff4.toInt(); //temp4
      //flow
      f1=rec.indexOf("|",f1);      //position of flow1
      f2=rec.indexOf("|",f1+1);   //position of flow2
      buff1=rec.substring(f1+1,f2); //get the string out
      buff2=rec.substring(f2+1);  //get the string out
      f1=buff1.toInt(); //flow1
      f2=buff2.toInt(); //flow2
      //save it to the SD card
      sendSD(t1,t2,t3,t4,f1,f2);
    } else // no exist signal "t" and "f" at the same time
    {
      D_PRINTLN(F("Not recognized command!"));
    }// end if else
  }// end if
}// end masterGet
//--------------------------------
#endif // __NANO_SD_CPP