#ifndef main
#define main

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include "motor.h"
#include  "distance.h"

/*User Defines*/
#define _VERSION "0.2"
#define _DEBUGMODE 0
#define _MOTORDEBUG 0

/*Wi-Fi Message*/
typedef struct espnow_msg_struct {
    char id; // must be unique for each sender board
    char data;
} espnow_msg_struct;

/*Wi-Fi SSID and Password*/
const char* ssid     = "Whimsical-Blue";
const char* password = "123456789";

/*ESPNow receive data structure*/
typedef struct struct_message_espnow {
  int id;
  int isActive;
  unsigned int data;
} struct_message_espnow;

enum sensorChecker{NO_OBSTACLES, SIDE_SENSOR_ALARM, FRONT_SENSOR_ALARM};

volatile long echo_start = 0;                         // Records start of echo pulse 
volatile long echo_end = 0;                           // Records end of echo pulse
volatile long echo_duration = 0;                      // Duration - difference between end and start
volatile int trigger_time_count = 0;                  // Count down counter to trigger pulse time

#endif