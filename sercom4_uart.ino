#include <Arduino.h>   // required before wiring_private.h
#include "wiring_private.h" // pinPeripheral() function

#define UART1_RX A2
#define UART1_TX A1

Uart Serial2 (&sercom4, UART1_RX, UART1_TX, SERCOM_RX_PAD_1, UART_TX_PAD_0);
void SERCOM4_Handler()
 {
   Serial2.IrqHandler();
 }

void setup() {
  SerialUSB.begin(9600); // Initialize Serial Monitor USB
  Serial2.begin(9600); // Initialize hardware serial port, pins 0/1

  while (!SerialUSB) ; // Wait for Serial monitor to open
  
  // Assign pins SERCOM functionality
  pinPeripheral(UART1_RX, PIO_SERCOM_ALT);
  pinPeripheral(UART1_TX, PIO_SERCOM_ALT);
  
  // Send a welcome message to the serial monitor:
  SerialUSB.println("Send character(s) to relay it over Serial2");
}

void loop()
{
  if (SerialUSB.available()) // If data is sent to the monitor
  {
    String toSend = ""; // Create a new string
    while (SerialUSB.available()) // While data is available
    {
      // Read from SerialUSB and add to the string:
      toSend += (char)SerialUSB.read();
    }
    // Print a message stating what we're sending:
    SerialUSB.println("Sending " + toSend + " to Serial2");

    // Send the assembled string out over the hardware
    // Serial2 port (TX pin 1).
    Serial2.print(toSend);
  }

  if (Serial2.available()) // If data is sent from device
  {
    String toSend = ""; // Create a new string
    while (Serial2.available()) // While data is available
    {
      // Read from hardware port and add to the string:
      toSend += (char)Serial2.read();
    }
    // Print a message stating what we've received:
    SerialUSB.println("Received " + toSend + " from Serial2");
  }
}
