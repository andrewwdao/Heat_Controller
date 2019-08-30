/*------------------------------------------------------------*-
  RELAY operation file
  ESP32 DEVKIT V1
  (c) An Minh Dao 2019
  version 1.00 - 14/08/2019
---------------------------------------------------------------
 * ESP-IDF version: 3.2
 * Compiler version: 5.2.0
 * Arduino components version: latest
--------------------------------------------------------------*/
#include "ESP32_Relay.h"

void setup() {
  relay_init();
}

void loop() {
  relay01(ON);
  delay(3000);
  relay01(OFF);
  delay(3000);
  relay02(ON);
  delay(3000);
  relay02(OFF);
  delay(3000);
  relay03(ON);
  delay(3000);
  relay03(OFF);
  delay(3000);
}
