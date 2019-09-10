/*------------------------------------------------------------*-
  NVS - non volatile system - function file
  ESP32 DEVKIT V1
  (c) Can Tho University 2019
  version 1.00 - 27/08/2019
---------------------------------------------------------------
 *
 * NOTE:  - StringBuffer.c_str() return const char* => it converts String into const char*
 *        - sprintf(charWriteBuffer,"%s", RAMdata.c_str()); //this function transfer const char* to char*
 *       
 * 
 --------------------------------------------------------------*/
#ifndef _ESP32_NVS_CPP
#define _ESP32_NVS_CPP
#include "ESP32_NVS.h"


// ------ Private constants -----------------------------------

// ------ Private function prototypes -------------------------

// ------ Private variables -----------------------------------

// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
// WARNING: address is a page address, 6-bit end will wrap around
// also, data can be maximum of about 30 bytes
void NVS_PID_write(float nkp,float nki,float nkd) {
    Preferences preferences; /* create an instance of Preferences library */
    preferences.begin("PID", false);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
    preferences.putBool("validPID", true);
    preferences.putFloat("Kp", nkp);
    preferences.putFloat("Ki", nki);
    preferences.putFloat("Kd", nkd);
    preferences.end();
}//end NVS_system_write
//------------------------------------------
float NVS_read_Kp() {
    Preferences preferences; /* create an instance of Preferences library */
    preferences.begin("PID", true);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
    bool hasState = preferences.getBool("validPID", false); //false is the default value
	  if (hasState) {
		  float currentKp = preferences.getFloat("Kp",0);
      preferences.end();
      return currentKp;
    } else {
		  preferences.end();
      return 0;
    }//end if else
    return 0;
}//end NVS_read_Kp
//------------------------------------------
float NVS_read_Ki() {
    Preferences preferences; /* create an instance of Preferences library */
    preferences.begin("PID", true);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
    bool hasState = preferences.getBool("validPID", false);
    if (hasState) {
      float currentKi = preferences.getFloat("Ki",0);
      preferences.end();
      return currentKi;
    } else {
      preferences.end();
      return 0;
    }//end if else
    return 0;
}//end NVS_read_Kp
//------------------------------------------
float NVS_read_Kd() {
    Preferences preferences; /* create an instance of Preferences library */
    preferences.begin("PID", true);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
    bool hasState = preferences.getBool("validPID", false);
    if (hasState) {
      float currentKd = preferences.getFloat("Kd",0);
      preferences.end();
      return currentKd;
    } else {
      preferences.end();
      return 0;
    }//end if else
    return 0;
}//end NVS_read_Kp
//------------------------------------------
void NVS_Temp_write(int T1,int T2,int T3,int T4) {
    Preferences preferences; /* create an instance of Preferences library */
    preferences.begin("Temp", false);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
    preferences.putBool("validTemp", true);
    preferences.putInt("T1", T1);
    preferences.putInt("T2", T2);
    preferences.putInt("T3", T3);
    preferences.putInt("T4", T4);
    preferences.end();
}//end NVS_system_write
//------------------------------------------
int NVS_read_T1() {
    Preferences preferences; /* create an instance of Preferences library */
    preferences.begin("Temp", true);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
    bool hasState = preferences.getBool("validTemp", false);
    if (hasState) {
      int currentT = preferences.getInt("T1",0);
      preferences.end();
      return currentT;
    } else {
      preferences.end();
      return 0;
    }//end if else
    return 0;
}//end NVS_read_T1
//------------------------------------------
int NVS_read_T2() {
    Preferences preferences; /* create an instance of Preferences library */
    preferences.begin("Temp", true);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
    bool hasState = preferences.getBool("validTemp", false);
    if (hasState) {
      int currentT = preferences.getInt("T2",0);
      preferences.end();
      return currentT;
    } else {
      preferences.end();
      return 0;
    }//end if else
    return 0;
}//end NVS_read_T2
//------------------------------------------
int NVS_read_T3() {
    Preferences preferences; /* create an instance of Preferences library */
    preferences.begin("Temp", true);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
    bool hasState = preferences.getBool("validTemp", false);
    if (hasState) {
      int currentT = preferences.getInt("T3",0);
      preferences.end();
      return currentT;
    } else {
      preferences.end();
      return 0;
    }//end if else
    return 0;
}//end NVS_read_T3
//------------------------------------------
int NVS_read_T4() {
    Preferences preferences; /* create an instance of Preferences library */
    preferences.begin("Temp", true);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
    bool hasState = preferences.getBool("validTemp", false);
    if (hasState) {
      int currentT = preferences.getInt("T4",0);
      preferences.end();
      return currentT;
    } else {
      preferences.end();
      return 0;
    }//end if else
    return 0;
}//end NVS_read_T4
//------------------------------------------
void NVS_Flow_write(int F1,int F2) {
    Preferences preferences; /* create an instance of Preferences library */
    preferences.begin("Flow", false);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
    preferences.putBool("validFlow", true);
    preferences.putInt("F1", F1);
    preferences.putInt("F2", F2);
    preferences.end();
}//end NVS_system_write
//------------------------------------------
int NVS_read_F1() {
    Preferences preferences; /* create an instance of Preferences library */
    preferences.begin("Flow", true);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
    bool hasState = preferences.getBool("validFlow", false);
    if (hasState) {
      int currentF = preferences.getInt("F1",0);
      preferences.end();
      return currentF;
    } else {
      preferences.end();
      return 0;
    }//end if else
    return 0;
}//end NVS_read_F1
//------------------------------------------
int NVS_read_F2() {
    Preferences preferences; /* create an instance of Preferences library */
    preferences.begin("Flow", true);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
    bool hasState = preferences.getBool("validFlow", false);
    if (hasState) {
      int currentF = preferences.getInt("F2",0);
      preferences.end();
      return currentF;
    } else {
      preferences.end();
      return 0;
    }//end if else
    return 0;
}//end NVS_read_F2
//------------------------------------------
#endif //_ESP32_NVS_CPP
