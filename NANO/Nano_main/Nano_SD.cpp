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

// ------ Private variables -----------------------------------

// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
bool SD_init()
{
  if (!SD.begin(10)) 
 {
    D_PRINTLN(F("sd initialization failed!"));
    return false;
 }
  D_PRINTLN(F("sd initialization done."));
  return true;
}
//----------------------------------------------------------
void sendSD(int temp1,int temp2,int temp3,int temp4, int flow1,int flow2)
{ 
  Time t;
  File Data=SD.open("data.txt",FILE_WRITE); // create FILE data.txt
  if(Data)
  { 
    D_PRINTLN(F("saving..."));
    Data.print(RTC_getTime());
    Data.print("_T1:");Data.print(temp1);
    Data.print("_T2:");Data.print(temp2);
    Data.print("_T3:");Data.print(temp3);
    Data.print("_T4:");Data.print(temp4);
    Data.print("_F1:");Data.print(flow1);
    Data.print("_F2:");Data.print(flow2);
    Data.print("\r\n");
    D_PRINTLN(F("done."));
    } else {
    D_PRINTLN(F("error"));
  }//end if else
  Data.close();
}// end sendSD
//--------------------------------
#endif // __NANO_SD_CPP
