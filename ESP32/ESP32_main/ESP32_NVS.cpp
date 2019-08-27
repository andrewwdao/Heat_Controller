///*------------------------------------------------------------*-
//  RAM usage of the RTC module DS3231 (AT24C32) - function file
//  ESP32 CORE0 - PROTOCOL CORE
//  (c) An Minh Dao 2019
//  version 2.00 - 10/03/2019
//---------------------------------------------------------------
// *  IC: AT24C32
// *  Share space and battery with IC RTC DS3231
// *  Data will be maintained as long as the battery is alive
// *  Available RAM: 32kB 
// *  Address start from 0 to 32768 (an address coresponding to a byte)
// *  Communication: I2C - SCL:22, SDA:21 (esp32)
// *  ESP32 GPIO:
// *      SDA:21
// *      SCL:22
// * 
// *  PUBLIC FUNCTIONS CONTAIN:
// *  void RAM_write(unsigned int RAMaddress, byte data); //write in 1 byte
// *  void RAM_page_write(unsigned int RAMaddress, byte* RAMdata, byte RAMlength); //write an array, should be less than 30 bytes
// *  byte RAM_read(unsigned int RAMaddress); //read in 1 byte
// *  void RAM_page_read(unsigned int RAMaddress, byte* RAMbuffer, byte RAMlength); //read an array, should be less than 30 bytes
// *  
// *  PRIVATE FUNCTIONS CONTAIN:
// * 
// * 
// * NOTE:  - StringBuffer.c_str() return const char* => it converts String into const char*
// *        - sprintf(charWriteBuffer,"%s", RAMdata.c_str()); //this function transfer const char* to char*
// *       
// * 
// --------------------------------------------------------------*/
//#ifndef _ESP32_NVS_CPP
//#define _ESP32_NVS_CPP
//#include "ESP32_NVS.h"
//
//
//// ------ Private constants -----------------------------------
//
//// ------ Private function prototypes -------------------------
//
//// ------ Private variables -----------------------------------
//
//// ------ PUBLIC variable definitions -------------------------
//
////--------------------------------------------------------------
//// FUNCTION DEFINITIONS
////--------------------------------------------------------------
//// WARNING: address is a page address, 6-bit end will wrap around
//// also, data can be maximum of about 30 bytes
//void NVS_system_write(SystemState SYSstate) {
//    Preferences preferences; /* create an instance of Preferences library */
//    preferences.begin("SysState", false);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
//    preferences.putBool("validSYS", true);
//    preferences.putInt("main", (int)SYSstate);
//    preferences.end();
//}//end NVS_system_write
//SystemState NVS_system_read() {
//    Preferences preferences; /* create an instance of Preferences library */
//    preferences.begin("SysState", true);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
//    bool hasState = preferences.getBool("validSYS", false);
//	if (hasState) {
//		int SYSstate = preferences.getInt("main",SYS_FAILED);
//        preferences.end();
//        //S_PRINTLN(hasState);
//        return (SystemState)SYSstate;
//    } else {
//		preferences.end();
//        return SYS_FAILED;
//    }//end if else
//}//end NVS_system_read
//
//void NVS_AExMode_write(bool Emode) {
//    Preferences preferences; /* create an instance of Preferences library */
//    preferences.begin("ExMode", false);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
//    preferences.putBool("valid", true);
//    preferences.putBool("main", Emode);
//    preferences.end();
//}//end NVS_ExMode_write
//bool NVS_AExMode_read() {
//    Preferences preferences; /* create an instance of Preferences library */
//    preferences.begin("ExMode", true);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
//    bool hasState = preferences.getBool("valid", false);
//	if (hasState) {
//		int AEstate = preferences.getBool("main",false); // AUTO EXPORT mode default is OFF
//        preferences.end();
//        return AEstate;
//    } else {
//		preferences.end();
//        return false;// AUTO EXPORT mode default is OFF
//    }//end if else
//}//end NVS_ExMode_read
//
//void NVS_WIFIdata_write(String WSSID, String WPASS) {
//    Preferences preferences; /* create an instance of Preferences library */
//    preferences.begin("WiFiInfo", false);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
//    preferences.putString("WSSID", WSSID);
//    preferences.putString("WPASS", WPASS);
//    preferences.putBool("valid", true);
//    preferences.end();
//}//end NVS_WIFIdata_write
//void NVS_WIFIdata_delete() {
//    Preferences preferences; /* create an instance of Preferences library */
//    preferences.begin("WiFiInfo", false);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
//    preferences.clear();
//	preferences.end();
//}//end NVS_WIFIdata_delete
//String NVS_wifiSSID_read() {
//    Preferences preferences;
//	preferences.begin("WiFiInfo", true);
//	bool hasPref = preferences.getBool("valid", false);
//	if (hasPref) {
//		String wifiSSID = preferences.getString("WSSID","");
//        preferences.end();
//        return wifiSSID;
//    } else {
//		preferences.end();
//        return "N/A";
//    }//end if else
//}//end NVS_wifiSSID_read
//String NVS_wifiPASS_read() {
//    Preferences preferences;
//	preferences.begin("WiFiInfo", true);
//	bool hasPref = preferences.getBool("valid", false);
//	if (hasPref) {
//		String wifiPASS = preferences.getString("WPASS","");
//        preferences.end();
//        return wifiPASS;
//    } else {
//		preferences.end();
//        return "N/A";
//    }//end if else
//}//end NVS_wifiPASS_read
//
//void NVS_WebAP_write(String AcessPoint) {
//    Preferences preferences; /* create an instance of Preferences library */
//    preferences.begin("HTTP", false);/* Start a namespace "WifiInfo",in Read-Write mode: set second parameter to false. Note: Namespace name is limited to 15 chars */
//    preferences.putString("httpAP", AcessPoint);
//    preferences.putBool("valid", true);
//    preferences.end();
//}//end NVS_WebAP_write
//String NVS_WebAP_read() {
//    Preferences preferences;
//	preferences.begin("HTTP", true);
//	bool hasPref = preferences.getBool("valid", false);
//	if (hasPref) {
//		String APoint = preferences.getString("httpAP","");
//        preferences.end();
//        return APoint;
//    } else {
//		preferences.end();
//        return "N/A";
//    }//end if else
//}//end NVS_WebAP_read
//#endif //_ESP32_NVS_CPP
