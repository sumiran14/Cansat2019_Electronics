void initXBee(){
  //zigbee.begin(9600); //Already in setup() of cansat_ 
   xbee.onReceive(onRecieveData);
}
//
void onRecieveData(){
  char i = xbee.read();
  while(xbee.available()){
    xbee.read();
  }
  switch(i){
    case '0':Serial.println("Recieved 0");
           break;
    case '1':Serial.println("Recieved 1"); 
            break;
     //and so on
  }
}
//
////For transmitting data, function is in i_packet.ino
