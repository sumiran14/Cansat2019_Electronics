#include <RTClib.h>
#include <Arduino.h>   // required before wiring_private.h
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <RTCZero.h>

#include <Adafruit_BMP280.h>
#include "MPU6050_tockn.h"
#include "packet.h"

#define voltagePin A8

#define gps_uart Serial2
#define zigbee Serial1
#define SD_SELECT 10

#define LOG_MISSION	//enable this to log mission events to SD card
#define SER_DEBUG		//enable this to get debug info in serial monitor
#define TEAM_ID 1516		//BAGS
