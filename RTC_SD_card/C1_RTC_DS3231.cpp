/*------------------------------------------------------------*-
  Module RTC using DS3231 - functions file
  ESP32 CORE1 - APPLICATION CORE
  (c) An Minh Dao 2019
  version 1.30 - 10/02/2019
---------------------------------------------------------------
 *  PUBLIC FUNCTIONS CONTAIN:
 *  void RTC_init();
 *  void RTC_setTime(); //only exist on DEBUG MODE
 *  void RTC_setCurrentTime();
 *  void RTC_getTime();
 *   
 *  PRIVATE FUNCTIONS CONTAIN:
 *  String RTC_GetData(); //only exist on DEBUG MODE
 *  
 --------------------------------------------------------------*/
#ifndef _C1_RTC_DS3231_CPP
#define _C1_RTC_DS3231_CPP
#include "C1_RTC_DS3231.h"

// ------ Private constants -----------------------------------
static const String RTC_FAILED = "RTC Failed! Proceed anyway...";
// ------ Private function prototypes -------------------------
static void startSNTP();
static String GetData(); //dependance of RTC_setTime in .h file
static bool getTimeFromSNTP();
// ------ Private variables -----------------------------------
RTC_DS3231 rtc;
// ------ PUBLIC variable definitions -------------------------

//--------------------------------------------------------------
// FUNCTION DEFINITIONS
//--------------------------------------------------------------
bool RTC_init() {
    char i_rtc=0;
    while (!rtc.begin()) {
        D_PRINTLN(F("Couldn't find RTC"));
        vTaskDelay(500 / portTICK_PERIOD_MS);
        if (i_rtc++>15) {
          S_PRINTLN(F("No RTC module! Proceed anyway..."));
          return false;
        }//end if
    }//end while
    i_rtc=0;
    while (rtc.lostPower()) {
        vTaskDelay(500 / portTICK_PERIOD_MS);
        if (i_rtc++>2) {break;}
    }//end while
    while (rtc.lostPower()) {
        if (wifi_isConnected()) {
            S_PRINTLN(F("RTC is NOT running!"));
            if (getTimeFromSNTP()) {return true;}
        }//end if
        else {S_PRINTLN(RTC_FAILED);return false;}
    }//end while

    return true;
}//end RTC_init

void RTC_Serial_updater() {
  //------------------------RESET RTC MANUALLY--------------------
  oled_RTC_SerialUpdater();
  RTC_tryAgain:
  S_PRINTLN();
  S_PRINTLN(F("\t\t\t---RTC SERIAL UPDATER---"));
  S_PRINTLN(F("Hello there!"));
  S_PRINTLN(F("I can help you manually fix the time "));
  S_PRINTLN(F("CAUTION : use NO LINE ENDING mode to type!!!"));
  S_PRINTLN(F("Ready to update your time?  Y/N"));
  long Rlastmillis=millis();
  while (Serial.available()==0) {
    if (SW_midPressed()) {//only activated when a press and a release is recognized
      NVS_system_write(SYS_NORMAL);
      S_PRINTLN(MES_NORMAL);
      ESP.restart();
    }//end if
    if ((millis()-Rlastmillis)>7000) {goto RTC_tryAgain;}  
  } // end while no signal
  while (Serial.available()> 0) {//some signal appeared
    char ch = Serial.read();
    if (ch=='y'||ch=='Y') {
        S_PRINTLN(F("'YES' Recieved"));
        int RTC_year, RTC_month, RTC_date, RTC_hour, RTC_minutes, RTC_second;
        S_PRINTLN(F("Type in new YEAR:"));
        RTC_year=GetData().toInt();
        S_PRINTLN(F("Type in new MONTH:"));
        RTC_month=GetData().toInt();
        S_PRINTLN(F("Type in new DATE:"));
        RTC_date=GetData().toInt();
        S_PRINTLN(F("Type in new HOUR:"));
        RTC_hour=GetData().toInt();
        S_PRINTLN(F("Type in new MINUTE:"));
        RTC_minutes=GetData().toInt();
        S_PRINTLN(F("Type in new SECOND:"));
        RTC_second=GetData().toInt();
        rtc.adjust(DateTime(RTC_year, RTC_month, RTC_date, RTC_hour, RTC_minutes, RTC_second));
        S_PRINT(F("Reset completed! Current time: "));S_PRINTLN(RTC_getTime());
    }//end yes
    else {
      S_PRINTLN(F("'NO' Recieved"));
    }//end no
    NVS_system_write(SYS_NORMAL);
    S_PRINTLN(MES_NORMAL);
    ESP.restart();
    }//end while serial available
}//end RTC_Serial_updater

void RTC_SNTP_updater() {
    //------------------------RESET RTC AUTOMATICALLY--------------------
    oled_RTC_SNTPupdater1();
    SNTPAgain:
    wifi_STA_init();
    oled_RTC_SNTPupdater2();
    if (wifi_isConnected()) {
        if (getTimeFromSNTP()) {oled_RTC_SNTPupdater3(true);}
        else                   {oled_RTC_SNTPupdater3(false);goto SNTPAgain; }
    }
    delay(2000);
    NVS_system_write(SYS_NORMAL);
    S_PRINTLN(MES_NORMAL);
    ESP.restart();
}//end RTC_SNTP_updater

String RTC_getTime() {
  DateTime now = rtc.now();
  String CurrentDay = ((String)now.hour()) + ':' + ((String)now.minute()) + ':' + ((String)now.second()) + '-' + 
                      ((String)now.day()) + '/' + ((String)now.month()) + '/' + ((String)now.year());
  return CurrentDay;
}//end RTC_getTime

String RTC_getDay() {
  DateTime now = rtc.now();
  String Ryear  = ((String)now.year());
  String Rmonth = (now.month()<10)?('0'+(String)now.month()):((String)now.month());
  String Rday   = (now.day()<10)?('0'+(String)now.day()):((String)now.day());
  String CurrentDay = Ryear+'/'+Rmonth+'/'+Rday;
  return CurrentDay;
}//end RTC_getTime

String RTC_getClock() {
  DateTime now = rtc.now();
  uint8_t tempHour = now.hour();
  uint8_t tempMin  = now.minute();
  if ((tempHour>24)||(tempMin>60)) {return "";}
  String C_hour   = (tempHour>9)?((String)tempHour):('0'+(String)tempHour);
  String C_minute = (tempMin>9)?((String)tempMin):('0'+(String)tempMin);
  return (C_hour + ':' + C_minute);
}//end RTC_getClock

uint8_t RTC_getSecond() {
  DateTime now = rtc.now();
  return now.second();
}//end RTC_getSecond

static void startSNTP() { //read more about SNTP - at: http://www.cems.uwe.ac.uk/~irjohnso/coursenotes/uwe/ntp.htm
	ip_addr_t addr;
	sntp_setoperatingmode(SNTP_OPMODE_POLL);
	inet_pton(AF_INET, "129.6.15.29", &addr); // Read more: https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/ipton.htm
	sntp_setserver(0, &addr);
	sntp_init();
}//end startSNTP

static String GetData() {
  String data = "";
  while(Serial.available()==0) {}// do nothing...
  while(Serial.available()>0) {//Nhan du lieu
    char ch = Serial.read();
    data = data + ch;
    delay(2); //for stablize
  }//end while serial available
  S_PRINT(F("Recieved: "));S_PRINTLN(data);
  return data;
}//end GetData

static bool getTimeFromSNTP() {
    startSNTP();
	time_t t; //there is a type of variable called "time"
    struct tm tm; //special struct to extract the time value into readable time
	char j=0;
    while(time(&t) < 1000) { //geting time from SNTP server
		D_PRINTLN(F("Waiting for SNTP ..."));
		vTaskDelay(3000/portTICK_PERIOD_MS);
        if (j++>20) {S_PRINTLN(RTC_FAILED);sntp_stop();return false;}
	}//end while, now we have the current time in *t variable (&t is the adress of the pointer)
	gmtime_r(&t, &tm); //extract variable time into readable time saved in struct, read more: https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_71/rtref/gmtimer.htm
    rtc.adjust(DateTime(tm.tm_year-100, tm.tm_mon+1, tm.tm_mday, tm.tm_hour+7, tm.tm_min, tm.tm_sec)); //see above link about gmtime_r to see how tm.tm_year and the rest defined
    sntp_stop();
    #ifdef ESP32_DEBUG
    char time_buffer[30]; //a string of char to hold time value
    asctime_r(&tm, time_buffer); //convert time struct into a character string, read more: https://www.ibm.com/support/knowledgecenter/ssw_ibm_i_71/rtref/asctimr.htm#asctimr
    D_PRINT(F("Coordinated Universal Time is: (GMT+0) ")); D_PRINTLN(time_buffer);
    #endif
    S_PRINT(F("Reset completed! Current time: (GMT+7) ")); S_PRINTLN(RTC_getTime());
    return true;
}//end getTimeFromSNTP

#endif //_C1_RTC_DS3231_CPP