int voltagePin=A3;
void setup(){
  initBatteryVoltage();
	SerialUSB.begin(115200);
}
void loop(){
	SerialUSB.println(String(getBatteryVoltage())+"\n");
  delay(1000);
}
