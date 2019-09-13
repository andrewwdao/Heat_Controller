/*-------------------------------------------
  UART - functions file
  ARDUINO NANO
  (c) Can Tho University 2019 
  version 1.10 - 25/08/2019
----------------------------------------------
 * All test function used with UART to USB has
 * to be in "No line ending" mode
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
  Serial.begin(57600);
}
//------------------------------------------------------------
void UART_isMasterReady() {
  bool notReady=true;
  while (notReady) {
     if( Serial.available()) {//if something appear in the serial monitor
        if (Serial.read()=='K') {
          String buff=Serial.readString();
          if (buff==AUTHORIZED_KEY) {
            D_PRINTLN(F("Give me the set values"));
            Serial.print(F("Updated!"));delay(3000);Serial.print(F("Updated!")); //repeat to make sure the master receive the data
            while (notReady) {
              if( Serial.available()) {//if something appear in the serial monitor
                if (Serial.read()=='S') { //S|Kp|Ki|Kd|F1|F2|T1|T2|T3|T4
                  uint16_t t1,t2,t3,t4;
                  float mpid[3]={0,0,0};
                  uint16_t mtemp[4]={0,0,0,0};
                  uint16_t mflow[2]={0,0};
                  String mKp="",mKi="",mKd="",mT1="",mT2="",mT3="",mT4="",mF1="",mF2="",rec="";
                  rec=Serial.readString();
                  t1 = rec.indexOf("|",0); //search for initial signal
                  if (t1>=0) { //has the correct signal
                  //set pid - flow values - temperature
                    t1=rec.indexOf("|",0);    //position of Kp
                    t2=rec.indexOf("|",t1+1); //position of Ki
                    t3=rec.indexOf("|",t2+1); //position of Kd
                    t4=rec.indexOf("|",t3+1); //position of flow1
                    mKp=rec.substring(t1+1,t2);//get the string out
                    mKi=rec.substring(t2+1,t3);//get the string out
                    mKd=rec.substring(t3+1,t4);//get the string out
                    t1=rec.indexOf("|",t4+1); //position of flow2
                    t2=rec.indexOf("|",t1+1); //position of temp1
                    mF1=rec.substring(t4+1,t1);//get the string out
                    mF2=rec.substring(t1+1,t2);//get the string out
                    t3=rec.indexOf("|",t2+1); //position of temp2
                    t4=rec.indexOf("|",t3+1); //position of temp3
                    t1=rec.indexOf("|",t4+1); //position of temp4
                    mT1=rec.substring(t2+1,t3);//get the string out
                    mT2=rec.substring(t3+1,t4);//get the string out
                    mT3=rec.substring(t4+1,t1);//get the string out
                    mT4=rec.substring(t1+1);   //get the string out
                    mpid[0] = mKp.toFloat(); //Kp
                    mpid[1] = mKi.toFloat(); //Ki
                    mpid[2] = mKd.toFloat(); //Kd
                    mtemp[0] = mT1.toInt(); //T1
                    mtemp[1] = mT2.toInt(); //T2
                    mtemp[2] = mT3.toInt(); //T3
                    mtemp[3] = mT4.toInt(); //T4
                    mflow[0] = mF1.toInt(); //Flow1
                    mflow[1] = mF2.toInt(); //Flow2
                    changeSetVal(mpid,mtemp,mflow);
                    Serial.print(F("Updated!"));delay(3000);Serial.print(F("Updated!")); //repeat to make sure the master receive the data
                    notReady=false;
                    return;
                  } else {
                    D_PRINTLN(F("Not recognized command!"));
                  }// end if else 
                }//end if
              }//end if
            }//end while
          }//end if
        }//end if
     }//end if
  }//end while
}//end UART_masterReady
//------------------------------------------------------------
 void UART_getFromMaster() //command: T|T1|T2|T3|T4_F|F1|F2 or P|Kp|Ki|Kd
{
  if( Serial.available()) //if something appear in the serial monitor
  { 
    char Ctemp = Serial.read();
    if (Ctemp=='T') { //if command is T|T1|T2|T3|T4_F|F1|F2
		  uint16_t t1,t2,t3,t4,f1,f2;
		  String buff1="",buff2="",buff3="",buff4="",rec="";
		  rec=Serial.readString();
		  t1=rec.indexOf("T",0); //search for initial signal - t for temperature
		  f1=rec.indexOf("F",0); //search for initial signal - f for flow
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
			  changeVal(t1,t2,t3,t4,f1,f2); //change it in the LCD screen
			  sendSD(t1,t2,t3,t4,f1,f2);//save it to the SD card
		  } else {// no exist signal "t" and "f" at the same time
			  D_PRINTLN(F("Not recognized command!"));
		  }// end if else
	  } else if (Ctemp=='P') { //if command is P|Kp|Ki|Kd
		    uint16_t p1,p2,p3;
		    float mpid[3]={0,0,0};
		    String mKp="",mKi="",mKd="",rec="";
        rec=Serial.readString();
        p1 = rec.indexOf("|",0); //search for initial signal
        if (p1>=0) { //has the correct signal
			    //set pid
          p1=rec.indexOf("|",0);    //position of Kp
          p2=rec.indexOf("|",p1+1); //position of Ki
          p3=rec.indexOf("|",p2+1); //position of Kd
			    mKp=rec.substring(p1+1,p2);//get the string out
          mKi=rec.substring(p2+1,p3);//get the string out
          mKd=rec.substring(p3+1);//get the string out
          mpid[0] = mKp.toFloat(); //Kp
          mpid[1] = mKi.toFloat(); //Ki
          mpid[2] = mKd.toFloat(); //Kd
          Serial.println(mpid[0]);
          Serial.println(mpid[1]);
          Serial.println(mpid[2]);
			    changeSetVal(mpid);
			    return;
        } else {
          D_PRINTLN(F("Not recognized command!"));
        }// end if else
	    } else {// not recognized command
		    D_PRINTLN(F("Not recognized command!"));
	    }// end if else
    }//end if
}// end getFromMaster
//--------------------------------
void PIDsendToMaster(float* Mpid) { //p|Kp|Ki|Kd
  char Smes[30];
  snprintf(Smes,30,"P|%d.%d|%d.%d|%d.%d",(int)*Mpid,(int)((*Mpid)*10)-((int)*Mpid)*10,(int)*(Mpid+1),(int)((*(Mpid+1))*10)-((int)*(Mpid+1))*10,(int)*(Mpid+2),(int)((*(Mpid+2))*10)-((int)*(Mpid+2))*10);
  Serial.println(Smes);
}//end PIDsendToMaster
//--------------------------------
void sTempSendToMaster(uint16_t* Mtemp) { //t|T1|T2|T3|T4
  char Smes[30];
  sprintf(Smes,"T|%d|%d|%d|%d",*(Mtemp),*(Mtemp+1),*(Mtemp+2),*(Mtemp+3));
  Serial.println(Smes);
}//end sTempSendToMaster
//--------------------------------
void sFlowSendToMaster(uint16_t* Mflow) { //f|F1|F2
  char Smes[30];
  sprintf(Smes,"F|%d|%d",*(Mflow),*(Mflow+1));
  Serial.println(Smes);
}//end sFlowSendToMaster
//--------------------------------
#endif // __NANO_UART_CPP
