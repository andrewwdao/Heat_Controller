/*-------------------------------------------
  SD CARD - header file
  ARDUINO NANO
  (c) Pham Thanh Tam - An Minh Dao 2019 
  version 1.10 - 05/08/2019
--------------------------------------------*/ 
#ifndef  __NANO_SD_CPP
#define  __NANO_SD_CPP
#include "Nano_SD.h"

// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------
/**
Send data to SD as: temp1, temp2, temp3, temp4, flow1, flow2
**/
void sendSD(int,int,int,int,int,int);
// ------ Private variables -----------------------------------

// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
bool SD_init()
{
  if (!SD.begin(10)) 
 {
    Serial.println("initialization failed!");
    return false;
 }
  Serial.println("initialization done.");
  return true;
}
//------------------------------------------------------------
 void getFromMaster()
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
			t1=rec.indexOf("|",0); 		//position of temp1
			t2=rec.indexOf("|",t1+1);	//position of temp2
			t3=rec.indexOf("|",t2+1);	//position of temp3
			t4=rec.indexOf("|",t3+1);	//position of temp4
			buff1=rec.substring(t1+1,t2);//get the string out
			buff2=rec.substring(t2+1,t3);//get the string out
			buff3=rec.substring(t3+1,t4);//get the string out
			buff4=rec.substring(t4+1);	 //get the string out
			t1=buff1.toInt(); //temp1
			t2=buff2.toInt(); //temp2
			t3=buff3.toInt(); //temp3
			t4=buff4.toInt(); //temp4
			//flow
			f1=rec.indexOf("|",0);			//position of flow1
			f2=rec.indexOf("|",f1+1);		//position of flow2
			buff1=rec.substring(f1+1,f2);	//get the string out
			buff2=rec.substring(f2+1); 	//get the string out
			f1=buff1.toInt(); //flow1
			f2=buff2.toInt(); //flow2
			//save it to SD card
			sendSD(t1,t2,t3,t4,f1,f2);
		} else // no exist signal "t" and "f" at the same time
		{
			Serial.println(F("Not recognized command!"));
		}// end if else
	}// end if
}// end masterGet
//----------------------------------------------------------
void sendSD(int temp1,int temp2,int temp3,int temp4, int flow1,int flow2)
{ 
  Time t;
  File Data=SD.open("data.txt",FILE_WRITE); // create FILE data.txt
  if(Data)
  { 
    Serial.print(F("Saving..."));
    Data.print(RTC_getTime());
    Data.print("_T1:");Data.print(temp1);
    Data.print("_T2:");Data.print(temp2);
    Data.print("_T3:");Data.print(temp3);
    Data.print("_T4:");Data.print(temp4);
    Data.print("_F1:");Data.print(flow1);
    Data.print("_F2:");Data.print(flow2);
    Data.print("\r\n");
    Serial.println(F("Done."));
    } else {
    Serial.println("Error");
  }//end if else
  Data.close();
}// end sendSD
//--------------------------------
#endif // __NANO_SD_CPP
