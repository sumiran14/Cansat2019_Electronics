#include <Arduino.h>   // required before wiring_private.h
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include "wiring_private.h" // pinPeripheral() function

#include "Adafruit_BMP280.h"
#include "MPU6050_tockn.h"
#include "packet.h"

#define UART0_RX 0	//defined by default //Serial1
#define UART0_TX 1

#define UART1_RX A2 //Serial2
#define UART1_TX A1

#define SDA 4 //Wire1
#define SCL 3

#define MOSI 11 //SPI1
#define MISO 12
#define SCK  13

#define voltagePin A3
#define SD_SELECT 10

#define Serial SerialUSB
#define gps_uart Serial1
#define zigbee Serial2

#define LOG_MISSION	//enable this to log mission events to SD card
#define SER_DEBUG		//enable this to get debug info in serial monitor
#define TEAM_ID 1516		//BAGS
