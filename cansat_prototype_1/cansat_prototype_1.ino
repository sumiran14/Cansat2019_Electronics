#include "pindef.h"

//Serial1 is defined by default
Uart Serial2 (&sercom4, UART1_RX, UART1_TX, SERCOM_RX_PAD_1, UART_TX_PAD_0);
TwoWire Wire1(&sercom2, SDA, SCL);
//SPI is defined by default.
//SPIClass SPI1(&sercom1, MISO, SCK, MOSI, SPI_PAD_0_SCK_1, SERCOM_RX_PAD_3);

Adafruit_BMP280 bmp;
MPU6050 mpu6050(Wire1);
packet dataPacket(TEAM_ID);

File packetFile;		//file handle for packet.csv
File missionLog;	//file handle for missin.log

long timer = 0;

void setup(){
	#ifdef SER_DEBUG
		Serial.begin(115200);
		while(!Serial);
  #endif
	gps_uart.begin(9600);
  zigbee.begin(9600);
  Wire1.begin();

  initSerial();	
  initBatteryVoltage();
	initBmp();
	initSD();
	mpu6050.begin();
  mpu6050.calcGyroOffsets();
	
	readFile("packet.csv");
	#ifdef LOG_MISSION
		logEvent("Altitude reset to 0.");
		delay(100);
		logEvent("Taking Off");
		delay(100);
	#endif
	readFile(&missionLog);
	
	//while(1);

	int i = 0;
	while(i<10){
		mpu6050.update();
		if(millis() - timer > 1000 ){
			i++;
			dataPacket.mission_time = millis();
			dataPacket.packet_count = i;
			dataPacket.altitude = bmp.readAltitude(1013.25);
			dataPacket.pressure = bmp.readPressure();
			dataPacket.temperature = bmp.readTemperature();
			dataPacket.voltage = getBatteryVoltage();
			
			dataPacket.pitch = mpu6050.getAngleX();
			dataPacket.roll  = mpu6050.getAngleY();
			
			dataPacket.software_state = idle;
			
			dataPacket.display();
			savePacket(&dataPacket);
			transmitPacketString(&dataPacket);
			
			timer = millis();
		}
	}
	
	readFile(&packetFile);
}

void loop(){
	
}
