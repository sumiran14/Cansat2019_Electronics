volatile unsigned long count = 0;

void initHall() {
  pinMode(HALLPIN, INPUT);
  count = 0;                        //Initializing count
  attachInterrupt(digitalPinToInterrupt(HALLPIN), raiseCount, CHANGE);  //HENCE increase of 2 when detected
}

void raiseCount(){                             
  count++;
}

long giveRPM(volatile unsigned long interruptStartTime){
  volatile unsigned long timeTaken = ((millis()/1000) - interruptStartTime); 
  volatile unsigned long noOfRotations = (count/NUMBEROFMAGNETS)/2;    //Detection of "numberOfMagnets" of counts equals 1 rotation in that time
  float rpm = (noOfRotations/timeTaken)*60;                       //Maths to get RPM
  return rpm;
}

void makeCountZero(){
  count = 0;
}

