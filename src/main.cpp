#include "main.h"

/*
Tasks:
*/

int distance_front_left, distance_front_right, distance_side_left, distance_side_right, distance_back;
int counter_front_left = 0, counter_front_right=0, counter_side_left=0, counter_side_right=0, counter_back=0;
int rand_number = 0;
int sensor_checker_status;
int counter = 0;
int random_movement;

espnow_msg_struct espnow_msg_receive;

int sensor_checker(int wait_time);
void getSensorDistances();

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
  getSensorDistances();
  rand_number=random(0, 100);

  //Not Recommended Stage
  /*
  while(distance_front_right>=400) {
    getSensorDistances();
    moveMotors(ROTATE_ON_LEFT_BWD);
    delay(50);
  }
  while(distance_front_left>=400) {
    getSensorDistances();
    moveMotors(ROTATE_ON_RIGHT_BWD);
    delay(50);
  }
  */
 
  //First Stage
  if(distance_front_right<=100 && distance_front_left<=100) {
    if(distance_back>=100) {
      while(distance_front_right<=110 || distance_front_left<=110) {
        getSensorDistances();
        moveMotors(GO_BACKWARD);
        delay(100);
      }
    }
    else {
      if(distance_side_left<=110) {
          moveMotors(TURN_LEFT);
          delay(400);
          moveMotors(GO_FORWARD);
          delay(400);
      }
      else if(distance_side_right<=110) {
          moveMotors(TURN_RIGHT);
          delay(400);
          moveMotors(GO_FORWARD);
          delay(400);
      }
    }
  }
  else if(distance_front_right<=100) {
    if(distance_front_left<=100) {
      getSensorDistances();
      moveMotors(GO_BACKWARD);
      delay(100);
    }
    if(distance_front_right>=60) {
      getSensorDistances();
      moveMotors(GO_BACKWARD);
      delay(100);
      moveMotors(ROTATE_ON_LEFT_BWD);
      delay(100);
      moveMotors(GO_FORWARD);
      delay(100);
      while(distance_side_right<FRONT_TRIG_SIDE_CTRL) {
        getSensorDistances();
        moveMotors(ROTATE_ON_LEFT_BWD);
        delay(400);
        moveMotors(GO_BACKWARD);
        delay(400);
      }
    }
    else {
      while (distance_front_right<80) {
        getSensorDistances();
        moveMotors(ROTATE_ON_LEFT_BWD);
        delay(400);
        moveMotors(GO_BACKWARD);
        delay(400);
      }
    }
  }
  else if(distance_front_left<=100) {
    if(distance_front_right<=100) {
      getSensorDistances();
      moveMotors(GO_BACKWARD);
      delay(100);
    }
    if(distance_front_left>=60) {
      getSensorDistances();
      moveMotors(ROTATE_ON_LEFT_BWD);
      delay(100);
      moveMotors(GO_BACKWARD);
      delay(100);
      moveMotors(GO_FORWARD);
      delay(100);
      while (distance_side_left<FRONT_TRIG_SIDE_CTRL) {
        getSensorDistances();
        moveMotors(ROTATE_ON_RIGHT_BWD);
        delay(400);
        moveMotors(GO_BACKWARD);
        delay(400);
      }
    }
    else {
      while (distance_front_left<80) {
        getSensorDistances();
        moveMotors(ROTATE_ON_RIGHT_BWD);
        delay(400);
        moveMotors(GO_BACKWARD);
        delay(400);
      }
    }
  }
  

  //Second Stage
    if((distance_front_left>=120 && distance_front_right>=120) && rand_number>=50) {
      int i = 0;
      if(rand_number>80) {
        while(i>=50) {
          getSensorDistances();
          moveMotors(GO_FORWARD);
          delay(20);
          i++;
        }
      }
      else if(rand_number<60 && rand_number>55) {
        while(i>=80) {
          getSensorDistances();
          moveMotors(TURN_LEFT);
          delay(20);
          i++;
        }
      }
      else if(rand_number<55 && rand_number>50) {
        while(i>=80) {
          getSensorDistances();
          moveMotors(TURN_RIGHT);
          delay(20);
          i++;
        }
      }
    }
    else if(distance_back>100 && (rand_number<=50 && rand_number > 30)) {
        int i=0;
        while(i>=80) {
          getSensorDistances();
          moveMotors(GO_BACKWARD);
          delay(20);
          i++;
        }
    }
    else if(distance_side_left>150 && rand_number > 15) {
        if(rand_number>22) {
          random_movement = ROTATE_ON_RIGHT_BWD;
        }
        else {
          random_movement = ROTATE_ON_LEFT_FWD;
        }
        int i = 0;
        while(i>=100) {
          getSensorDistances();
          moveMotors(random_movement);
          delay(20);
          i++;
        }
    }
    if(distance_side_right>150 && rand_number > 0) {
        if(rand_number>7) {
          random_movement = ROTATE_ON_RIGHT_FWD;
        }
        else {
          random_movement = ROTATE_ON_LEFT_BWD;
        }
        int i = 0;
        while(i>=100) {
          getSensorDistances();
          moveMotors(random_movement);
          delay(20);
          i++;
        }
    }
  }
}

void getSensorDistances() {
  distance_front_right = getDistance(sensorFrontRightTrig, sensorFrontRightEcho);
  distance_front_left = getDistance(sensorFrontLeftTrig, sensorFrontLeftEcho);
  distance_side_right = getDistance(sensorSideRightTrig, sensorSideRightEcho);
  distance_side_left = getDistance(sensorSideLeftTrig, sensorSideLeftEcho);
  distance_back = getDistance(sensorBackTrig, sensorBackEcho); 

  #if _DEBUGMODE
    Serial.print("cm front right: ");
    Serial.print(distance_front_right);
    Serial.print("|   cm front left: ");
    Serial.print(distance_front_left);
    Serial.print("|   cm side right: ");
    Serial.print(distance_side_right);
    Serial.print("|   cm side left: ");
    Serial.print(distance_side_left);
    Serial.print("|   cm back: ");
    Serial.println(distance_back);
    Serial.print("Random number: ");
    Serial.println(rand_number);
  #endif

  if(distance_front_right<CRICITAL_DISTANCE) {
    counter=0;
    moveMotors(TURN_RIGHT);
    delay(TURNING_ON_TWO_DELAY);
    moveMotors(GO_BACKWARD);
    delay(400);
    counter_front_right++;
  }
  if(distance_front_left<CRICITAL_DISTANCE) {
    counter=0;
    moveMotors(TURN_LEFT);
    delay(TURNING_ON_TWO_DELAY);
    moveMotors(GO_BACKWARD);
    delay(BACKWARD_DELAY);
    counter_front_left++;
  }
  if(distance_side_right<CRICITAL_DISTANCE) {
    counter=0;
    moveMotors(ROTATE_ON_RIGHT_FWD);
    delay(TURNING_ON_ONE_DELAY);
    counter_side_right++;
  }
  if(distance_side_left<CRICITAL_DISTANCE) {
    counter=0;
    moveMotors(ROTATE_ON_LEFT_FWD);
    delay(TURNING_ON_ONE_DELAY);
    counter_side_left++;
  }
  if(distance_back<CRICITAL_DISTANCE) {
    counter=0;
    moveMotors(GO_FORWARD);
    delay(FORWARD_DELAY);
    counter_back++;
  }
}
