/*------------------------------------------------------------*-
  MAIN - functions file
  ESP32 DEVKIT V1
  (c) Can Tho University - 2019
  version 1.00 - 14/08/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/



int UPDATE_INTERVAL = 10; //time interval to update data to the server




#ifdef SYSTEM_DEBUG
  #include "ESP32_debug.h"
#else
  #include "ESP32_stateFlow.h"
#endif


///////////////////////////////////////MAIN FUNCTION/////////////////////////////////////
// ---------------------------------- SETUP PROTOCOL -------------------------------------------
void setup() {
    
  #ifdef SYSTEM_DEBUG
    debug_init();
  #else
    System_init();
  #endif

}// end setup
// ---------------------------------- LOOP -------------------------------------------
void loop() {
  UART_getFromSlave();
  UART_sendToSlave(UPDATE_INTERVAL); //send data to slave every 10 second - you can change the interval as you want

  #ifdef SYSTEM_DEBUG
    system_debug();
  #else
    mainRoutine();
  #endif
  
}//end loop
