void initXBee(){
  //zigbee.begin(9600); //Already in setup() of TEENSY_PROTOTYPE1 
//   xbee.onReceive(onRecieveData);
  pinMode(XBEE_INTERRUPT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(XBEE_INTERRUPT_PIN), xbeeMessegeReceived, RISING);
}

//Function That will be executed by xbee interrupt
void xbeeMessegeReceived(){
  int x = xbee.parseInt();
  switch(x){
    case 0:Serial.println("Recieved 0");
            delay(1000);
           break;
    case 1:Serial.println("Recieved 1"); 
           break;
    default:Serial.println("Recieved something");
            break;
     //and so on
  }
}
//
////For transmitting data, function is in i_packet.ino
