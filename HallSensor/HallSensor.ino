

/*
 * Simple code to detect magnet and increase counter 
 * After every "resetInitialCountTime" seconds initialCount will will be pivot to current count
 * WHAT I DID:
 * I keep 
 */
#include <TimerOne.h>                             //Adding the Software Interrupt Library
#include <PinChangeInt.h>                         //Adding the Hardware interrupt Library

int resetInitialCountTime = 3000000;              //3000000 microsec or 3 sec
int numberOfMagnets = 3;                          //Number of magnets on fan 

int dPin = 2;   

int count = 0;

uint32_t initialCount = 0;            //Pivoting Value after every 3 second to compare count and calculating RPM
uint16_t initialCountTime = 0;        //This will store the time when we have reset our initial pivot

//=====================>> SETUP <<======================================
void setup() {
  pinMode(dPin, INPUT);
  Timer1.initialize(resetInitialCountTime);   //Initializing Software Interrupts
  Timer1.attachInterrupt(resetInitialCount);    //Attaching software interrupt
  
  attachInterrupt(digitalPinToInterrupt(dPin), raiseCount, FALLING); //Attaching the interrupts
  count = 0;                                                         //Initializing count
}
//=====================>> SETUP ENDS <<======================================
//=====================>> LOOP <<======================================
void loop() {
  float rpm = giveRPM();
}
//=====================>> LOOP ENDS <<=================================
/*
 * This function is called every time hall sensor detects magnets.
 * Called by Hardware Interrupt at digital pin
 * Function: Increase global variable count by 1
 */
int raiseCount(){                             
  count += 1;
}

/*
 * Called by software interrupts: 
 * Function: to reset the initialCount and Time
 */
void resetInitialCount(){            
  initialCount = count;
  initialCountTime = millis();
}

/*
 * RPM = number of rotations/time taken * 60
 *     = (count2 - count1)/(time2 - time1) * 60 .   (count is count per magnet)
 */
float giveRPM(){
  int numCounts = count - initialCount;                           //Comparing with pivot point- Finding difference between two counts
  float timeTaken = (float)(millis() - initialCountTime)/100.0;   //Converting unit of timeTaken in second after finding Time difference
  float noOfRotations = (float)numCounts/numberOfMagnets;         //Detection of "numberOfMagnets" of counts equals 1 rotation
  float rpm = (noOfRotations/timeTaken)*60;                       //Maths to get RPM
  return rpm;
}

