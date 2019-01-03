#include <Wire.h>  //This is the library that is used for I2C communication
#include "wiring_private.h"
int16_t accelX, accelY, accelZ;          //3 long : This will store the RAW data read from the accelerometer MPU itself
float gForceX, gForceY, gForceZ;      //3 floats:This will be used to calculate g-force acting in three direction

int16_t gyroX, gyroY, gyroZ;             //3 long : This will store the RAW data read from the gyro of the MPU itself
float rotX, rotY,rotZ;                //3 floats:This will be storing rotational speed or velocity around those axis

#define MPU9250ADDRESS 0b1101001 //0x69
#define Serial SerialUSB
TwoWire myWire(&sercom2, 4, 3); //SDA = 4, SCL = 3


void setup() {
  Serial.begin(9600);    
  while (!Serial) ; // Wait for Serial monitor to open   
  Serial.println("Started");          
  myWire.begin();         //-------->>>>//Command that we need to initialize our I2C communication
                                      //Abosultely a must before we start reading and writing any 
                                      //data from I2C enabled devices
                                      
  pinPeripheral(4, PIO_SERCOM_ALT);
  pinPeripheral(3, PIO_SERCOM_ALT);

  accelX = 0; accelY = 0; accelZ = 0;
  gyroX = 0; gyroY = 0; gyroZ = 0; 
  
  setupMPU();           //this is a function defined below
}

void loop() {
  recordAccelRegisters();
  recordGyroRegisters();
  printData();
  delay(300);
}

//MAIN PURPOSE OF SETUP MPU FUNCTION IS:
//1.) To establish communnication with the MPU.
//2.) Setup up all the registers which we will be using in order to read data back from the MPU in the arduino 
void setupMPU(){
//  Serial.println("In SetUpMPU");     
  //1. Implementaion of Power Manamegent Register
  myWire.beginTransmission(MPU9250ADDRESS);      //This is the I2C address of the MPU (b1101000/b1101001 for AD0 low/high datasheet sec. 9.2: I2C Interface)
  myWire.write(0x6B);                       //Accessing the register 6B (Decimal: 107) - Power Management (Sec. 4.28). This register deals with power management.
  myWire.write(0b00000000);                 //Setting SLEEP register to 0. (Required; see Note on p. 9). Seeing documentation, By setting reqd bits to 0, MPU is not in sleep mode or external clock mode. 
  myWire.endTransmission();  
  
  //2. Implementaion of Gyroscope Register
  myWire.beginTransmission(MPU9250ADDRESS);      //I2C address of the MPU
  myWire.write(0x1B);                       //Accessing the register 1B (Decimal: 27) - Gyroscope Configuration (Sec. 4.4) 
  myWire.write(0x00000000);                 //Setting the gyro to full scale +/- 250deg./s............ This range can be extended to +/-2000deg./s
  myWire.endTransmission(); 

  //3. Implementaion of Accelerometer Register
  myWire.beginTransmission(MPU9250ADDRESS);      //I2C address of the MPU
  myWire.write(0x1C);                       //Accessing the register 1C (Decimal: 28) - Acccelerometer Configuration (Sec. 4.5) 
  myWire.write(0b00000000);                 //Setting the accel to +/- 2g
  myWire.endTransmission(); 
  Serial.println("SetUpMPU finished");     

}

void recordAccelRegisters() {
//  Serial.println("recordAccelData");     
  myWire.beginTransmission(MPU9250ADDRESS);      //I2C address of the MPU............. Same used in setupMPU.
  myWire.write(0x3B);                       //Starting register for Accelerometer Readings
  myWire.endTransmission();
  myWire.requestFrom(MPU9250ADDRESS,6);          //Request Accelerometer Registers (3B to 40) i.e. from 6 registers
//  Serial.println("requestAccelData");
  while(myWire.available() < 6);            //myWire.available(): returns The number of bytes available for reading.
//  Serial.print("myWire.available() - Accelerometer : ");
  //C CODE: leftShift and or operator
  //In documentation each coressponds to 2 bytes. 1 byte = 8 byte.
  //myWire.read() gives 1 byte (8 bit) at a time and then every time we use it, it shift to next bit.
  accelX = myWire.read()<<8|myWire.read();    //Store first two bytes into accelX     //Multiply highByte by 256 and ad lowByte
  accelY = myWire.read()<<8|myWire.read();    //Store middle two bytes into accelY
  accelZ = myWire.read()<<8|myWire.read();    //Store last two bytes into accelZ
  processAccelData();
}

void processAccelData(){
  gForceX = accelX / 16384.0;           //As we have selected full scale range 2g, LSB Sensitivity = 16384 LSB/g
  gForceY = accelY / 16384.0;           //Therefore for example our MPU reads 20,000 then it is = 20,000/16384 g = 1.22 g 
  gForceZ = accelZ / 16384.0;
}

void recordGyroRegisters() {
//  Serial.println("recordGyroData");     

  myWire.beginTransmission(MPU9250ADDRESS);      //I2C address of the MPU
  myWire.write(0x43);                       //Starting register for Gyro Readings
  myWire.endTransmission();
  myWire.requestFrom(MPU9250ADDRESS,6);          //Request Gyro Registers (43 - 48)
  while(myWire.available() < 6);
  gyroX = myWire.read()<<8|myWire.read(); //Store first two bytes into accelX
  gyroY = myWire.read()<<8|myWire.read(); //Store middle two bytes into accelY
  gyroZ = myWire.read()<<8|myWire.read(); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
}

void printData() {
//    Serial.println("print Data");     

  Serial.print("Gyro (deg/s)");
  Serial.print(" X=");
  Serial.print(rotX);
  Serial.print(" Y=");
  Serial.print(rotY);
  Serial.print(" Z=");
  Serial.print(rotZ);
  Serial.print(" Accel (g)");
  Serial.print(" X=");
  Serial.print(gForceX);
  Serial.print(" Y=");
  Serial.print(gForceY);
  Serial.print(" Z=");
  Serial.print(gForceZ);
  
  float rollAngle = atan2 (gForceX,gForceZ)*180/3.14;  // arc tangent of Gx/Gz
  float pitchAngle = atan2 (gForceY,sqrt ((gForceX*gForceX) +(gForceZ*gForceZ)))*180/3.14;  // arc tangent of Gy/Sqrt(Gx^2 + Gy^2)
  
  Serial.print("\tRoll Angle = ");
  Serial.print(rollAngle);
  Serial.print(" \t Pitch Angle = ");
  Serial.println(pitchAngle);
}


