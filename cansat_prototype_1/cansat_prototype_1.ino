#include "pindef.h"

//Serial1 is defined by default
Uart Serial2 (&sercom4, UART1_RX, UART1_TX, SERCOM_RX_PAD_1, UART_TX_PAD_0);
TwoWire Wire1(&sercom2, SDA, SCL);
SPIClass SPI1(&sercom1, MISO, SCK, MOSI, SPI_PAD_0_SCK_1, SERCOM_RX_PAD_3);

Adafruit_BMP280 bmp;
MPU6050 mpu6050(Wire1);

File packetLog;		//file handle for packet.csv
File missionLog;	//file handle for missin.log

long timer = 0;

void setup(){
  Serial.begin(115200);
  while(!Serial);
  gps.begin(9600);
  zigbee.begin(9600);
  Wire1.begin();

  initSerial();	
  initBatteryVoltage();
	initBmp();
	mpu6050.begin();
	initSD();
	
	//readFile("packet.csv");
	#ifdef LOG_MISSION
		logEvent("Altitude reset to 0.");
		delay(100);
		logEvent("Taking Off");
		delay(100);
	#endif
	
	readFile(&missionLog);
	
	//while(1);
  
  mpu6050.calcGyroOffsets(true);
}

void loop(){
  mpu6050.update();

  if(millis() - timer > 1000){
    
    Serial.println("=======================================================");
    Serial.println("========================MPU============================");
    
    Serial.print("temp : ");Serial.println(mpu6050.getTemp());
    Serial.print("accX : ");Serial.print(mpu6050.getAccX());
    Serial.print("\taccY : ");Serial.print(mpu6050.getAccY());
    Serial.print("\taccZ : ");Serial.println(mpu6050.getAccZ());
  
    Serial.print("gyroX : ");Serial.print(mpu6050.getGyroX());
    Serial.print("\tgyroY : ");Serial.print(mpu6050.getGyroY());
    Serial.print("\tgyroZ : ");Serial.println(mpu6050.getGyroZ());
  
    Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
    Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());
  
    Serial.print("gyroAngleX : ");Serial.print(mpu6050.getGyroAngleX());
    Serial.print("\tgyroAngleY : ");Serial.print(mpu6050.getGyroAngleY());
    Serial.print("\tgyroAngleZ : ");Serial.println(mpu6050.getGyroAngleZ());
    
    Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
    Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
    Serial.print("\tangleZ : ");Serial.println(mpu6050.getAngleZ());

    Serial.println("========================BMP============================");
		
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println("========================BATTERY========================");
    Serial.println("Battery Voltage : " + String(getBatteryVoltage()));

    Serial.println("=======================================================");	
    timer = millis();   
  }	
}
