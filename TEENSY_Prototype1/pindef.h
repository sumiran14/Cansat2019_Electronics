#include <MPU6050_tockn.h>
#include <RTClib.h>    //RTC Library
#include <Arduino.h>   // required before wiring_private.h
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include <Adafruit_BMP280.h> //BMP Library
//#include "MPU6050_tockn.h"
#include "packet.h"

#define voltagePin A8

#define gps_uart Serial2

#define xbee Serial1
#define XBEE_INTERRUPT_PIN 2

#define SD_SELECT 10

#define NUMBEROFMAGNETS 1           //Number of magnets on fan 
#define HALLPIN 3

#define LOG_MISSION	//enable this to log mission events to SD card
#define SER_DEBUG		//enable this to get debug info in serial monitor
#define TEAM_ID 3279		//TEAM KALAM
