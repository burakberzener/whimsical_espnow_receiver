#include "main.h"

/*
Tasks:
*/

 /*Private Variables BEGIN*/

 /*Private Variables END*/

 /*Private Functions Define BEGIN*/

 /*Private Functions Define END*/

espnow_msg_struct espnow_msg_receive;

//callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&espnow_msg_receive, incomingData, sizeof(espnow_msg_receive));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("id: ");
  Serial.println(espnow_msg_receive.id);
  Serial.print("data: ");
  Serial.println(espnow_msg_receive.data);
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  //delay(4000);
  /*Device Informations*/
  Serial.write("Whimsical Software Version: ");
  Serial.println(_VERSION); 
  Serial.write("MAC Address of this device: ");
  Serial.println(WiFi.macAddress()); 


  /*Wi-Fi Init*/
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  /*Inits*/
  Serial.println("INITS");
  initMotors();
  Serial.println("Motors are initialised.");
  initDistance();
  Serial.println("Sensors are initialised.");
  randomSeed(analogRead(36));
  Serial.println("Random is initialised.");

  #if _DEBUGMODE
    while(counter<300) {
      rand_number=random(100);
      Serial.print("Random number: ");
      Serial.println(rand_number);
      counter++;
    }
    counter=0;
  #endif

  #if _MOTORDEBUG
    moveMotors(GO_FORWARD);
    delay(2000);
    moveMotors(GO_BACKWARD);
    delay(2000);
    moveMotors(TURN_RIGHT);
    delay(2000);
    moveMotors(TURN_LEFT);
    delay(2000);
    moveMotors(ROTATE_ON_LEFT_BWD);
    delay(2000);
    moveMotors(ROTATE_ON_LEFT_FWD);
    delay(2000);
    moveMotors(ROTATE_ON_RIGHT_BWD);
    delay(2000);
    moveMotors(ROTATE_ON_RIGHT_FWD);
    delay(2000);
    moveMotors(STOP_ALL);
  #endif
}
 
void loop() {
  Serial.println("******MAIN LOOP******");

  if(espnow_msg_receive.data == 'o') {
    /*Algo Code BEGIN*/

    /*Algo Code END*/
  }
}
 /*Private Functions BEGIN*/

 /*Private Functions END*/