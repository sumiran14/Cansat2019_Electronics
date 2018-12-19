/*
 * Simple code to detect magnet and increase counter 
 */

#include <PinChangeInt.h>                                           //Adding the required library
//int dOp;
//int aOp;

int dPin = 2;                                                       //Didital pin 2 connected to Hall Sensor Digital pin
//int aPin = A0;

int count = 0;

void setup() {
//  Serial.begin(9600);
  pinMode(dPin, INPUT);
//  pinMode(aPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(dPin), raiseCount, FALLING); //Attaching the interrupts
  count = 0;                                                         //Initializing count
}

void loop() {
//  dOp = digitalRead(dPin);
//  aOp = analogRead(aPin);
//  Serial.print(count);
//  Serial.print(" .) \t");
//  Serial.print(dOp);
//  Serial.print("\t");
//  Serial.println(aOp);
  

}
/*
 * This function is called every time hall sensor detects magnets.
 * Called by attachInterrupts
 * Function: Increase global variable count by 1
 */
int raiseCount(){                             
  count += 1;
}
