//IMPORTANT : MPU toc library change address to 0x69
            //AD0 pin high
#include "pindef.h"

packet dataPacket(TEAM_ID); 
uint64_t packetCount = 0;

//I2C Objects Initialization=================================
Adafruit_BMP280 bmp;    //BMP object: I2C interface //Used "Wire"
RTC_DS3231 rtc;         //RTC object: I2C interface //Used "Wire"
MPU6050 mpu6050(Wire);  //MPU6050 object
long timer = 0;
volatile unsigned long countStartTime = 0;
//File Objects for SDCARD
File packetFile;    //file handle for packet.csv
File missionLog;  //file handle for missin.log

void setup() {
  //Opening SErial Monitor
  Serial.begin(9600);
  while(!Serial);

  //I2C Devices Initialization======================================
  Wire.begin();         //I2C Wire initialization
  initBmp();            //BMP
  initRTC();            //RTC
  resetMissionTime();   //To initialize the startTime variable
  mpu6050.begin();      //MPU
  mpu6050.calcGyroOffsets(true);
  
  //UART Devices Initialization===============================
  xbee.begin(9600);       //XBEE initializing
  initXBee();
  //GPS LEFT
  
  //SPI Devices Initialization=====================================
  initSD();

  //Battery Voltage:
  initBatteryVoltage();
} 


void loop() {
  
  mpu6050.update();
  if(millis()-timer > 1000){
    packetCount++;
    //PACKET_COUNT
    dataPacket.packet_count = packetCount;
    //BMP=========================================================
    dataPacket.altitude = bmp.readAltitude(1013.25);
    dataPacket.pressure = bmp.readPressure();
    dataPacket.temperature = bmp.readTemperature();
    //RTC=========================================================
    dataPacket.mission_time = getMissionTime();
    //MPU=========================================================
    dataPacket.pitch = mpu6050.getAngleX();
    dataPacket.roll  = mpu6050.getAngleY();
    //VOLTAGE
    dataPacket.voltage = getBatteryVoltage();
    dataPacket.blade_spin_rate = giveRPM(countStartTime);
    makeCountZero();
    countStartTime = millis()/1000;
  
    dataPacket.display();
    //Sending data via xbee
    savePacket(&dataPacket);
    transmitPacketString(&dataPacket);
      
//    Serial.print(String(dataPacket.mission_time)+"\t"+String(dataPacket.altitude)+"\t"+String(dataPacket.pressure)+"\t"+String(dataPacket.temperature));
//    Serial.println("\t"+String(dataPacket.pitch)+"\t"+String(dataPacket.roll));
    
    timer = millis();
  }
}
