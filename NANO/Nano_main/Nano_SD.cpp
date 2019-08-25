/*-------------------------------------------
  SD CARD - header file
  ARDUINO NANO
  (c) Pham Thanh Tam - An Minh Dao 2019 
  version 1.10 - 05/08/2019
--------------------------------------------*/ 
#include "Nano_SD.h"

File Data;
int t1,t2,t3,t4,f1,f2; // 

/**
Sent data to SD
**/
void sentSD();

/**
Receive data from serial and send data to SD
**/
void rece();
//----------------------------------------------------------
void sentSD()
{ Time t;
  Data=SD.open("data.txt",FILE_WRITE); // create FILE data.txt
  if(Data)
  { 
    Serial.print("Senting");
    Data.print(RTC_getTime());
    Data.print("_T1:");
    Data.print(t1);
    Data.print("_T2:");
    Data.print(t2);
    Data.print("_T3:");
    Data.print(t3);
    Data.print("_T4:");
    Data.print(t4);
    Data.print("_F1:");
    Data.print(f1);
    Data.print("_F2:");
    Data.print(f2);
    Data.print("\r\n");
   
    }
    else
    Serial.println("Error");
  Data.close();
  }// end sentSD
//------------------------------------------------------------
 void rece()
{ int c1,c2,c3,c4,fl1,fl2,temp;
  String buff1="",buff2="",buff3="",buff4="",buff5="",buff6="",rec="";
  if( Serial.available())
  { 
    rec=Serial.readString();
    temp=rec.indexOf("t",0);
    if(temp>=0)
    {
		c1=rec.indexOf("|",0);
		c2=rec.indexOf("|",c1+1);
		c3=rec.indexOf("|",c2+1);
		c4=rec.indexOf("|",c3+1);
		buff1=rec.substring(c1+1,c2);
		buff2=rec.substring(c2+1,c3);
		buff3=rec.substring(c3+1,c4);
		buff4=rec.substring(c4+1);
		t1=buff1.toInt();
		t2=buff2.toInt();
		t3=buff3.toInt();
		t4=buff4.toInt();
	
    }// end if(t>=0)
    else
    {
       fl1=rec.indexOf("|",0);
       fl2=rec.indexOf("|",fl1+1);
       buff5=rec.substring(fl1+1,fl2);
       buff6=rec.substring(fl2+1); 
       f1=buff5.toInt();
       f2=buff6.toInt();
       sentSD();
    }// end else if(t>=0)
 }// end if(serial.availale());
 else
    Serial.println("don't receive ");
  
}// end receive();
//-------------------------------------------    
 void SD_init()
 {
  if (!SD.begin(10)) 
 {
    Serial.println("initialization failed!");
    while (1);
 }
  Serial.println("initialization done.");
  }
