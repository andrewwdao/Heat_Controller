/*  
 * (c) 2019 Can Tho University. All Rights Reserved.
 *  
 * NOTE: change RFID setting in config.h
 * 
 * CAUTION: must include config.h in the main .ino file
 */
void MQTT_init() {
  Wifi_begin();
  mqtt.will (LWT_TOPIC, LWT_PAYLOAD, MQTT_QOS_1, LWT_RETAIN); //Set up last will
  //mqtt.subscribe(&cmd1); // Set up MQTT subscriptions.

  MQTT_connect();
  lastmillis = millis();
  publishNow(availability,"online",RETAIN,"Status Failed to update!","Status updated!");

  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
}//end MQTT_init

void MQTT_maintain() {//keep the MQTT connection
    MQTT_connect(); //LED indicator integrated

    // Adjust PING time in seconds in Adafruit_MQTT.h:  
    //#define MQTT_CONN_KEEPALIVE 60 --> Default to 1 minutes.
    if (((millis()-lastmillis)>PING_WAIT)) {//wait for PING_WAIT msecond before ping the server to keep the mqtt connection alive
      char pingCount=0;
      while (! mqtt.ping()) {if(pingCount++>PING_TIMES) mqtt.disconnect();return;}// if ping PING_TIMES times and failed then disconnect
      lastmillis = millis(); //ping sucess
    }//end if
}//end MQTT_maintain

void Wifi_begin() {
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print(F("Connecting to "));
  Serial.print(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }//endif
  
  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));Serial.println(WiFi.localIP());
  Serial.println();
}//end wifi begin

//LED INDICATOR INTEGRATED INSIDE
void MQTT_connect() {// Ensure the connection to the MQTT server is alive (this will make the first connection and automatically reconnect when disconnected).
  
  if (mqtt.connected()) {digitalWrite(LED_BUILTIN,HIGH);return;} // Stop if already connected, turn on indicating LED

  digitalWrite(LED_BUILTIN,LOW); //if not connected, indicate by a LED
  Serial.println(F("Connecting to MQTT... "));
  int8_t ret;
  while ((ret = mqtt.connect()) != 0)  {         // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println(F("Retrying MQTT connection in 3 seconds..."));
    mqtt.disconnect();
    delay(3000);  // wait 3 seconds
  }//end while
  Serial.println(F("MQTT Connected!"));
}//end MQTT connect

//--------SELF CREATED QOS1 --make sure the packet made it to the broker
void publishNow(Adafruit_MQTT_Publish topicPub,const char* MQTTmessage, bool retained, const char* failed, const char* sucess) {
  char pub=1;
  while (!topicPub.publish(MQTTmessage,retained)) {Serial.println(F(failed));delay(PUB_WAIT);if (pub++>(PUB_RETRIES-1)) break;} 
  if (pub<(PUB_RETRIES)) {Serial.println(F(sucess));}
}//end publishNow
void publishNow(Adafruit_MQTT_Publish topicPub,int MQTTmessage, bool retained, const char* failed, const char* sucess) {
  char pub=1;
  while (!topicPub.publish(MQTTmessage,retained)) {Serial.println(F(failed));delay(PUB_WAIT);if (pub++>(PUB_RETRIES-1)) break;} 
  if (pub<(PUB_RETRIES)) {Serial.println(F(sucess));}
}//end publishNow
