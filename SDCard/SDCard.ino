/*

   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10

*/
#define LOG_EVENTS	//enable this to log mission events to SD card
#define SER_DEBUG		//enable this to get debug info in serial monitor

#include <SPI.h>
#include <SD.h>

const int sd_select = 10;

File packetLog;
String fileName = "packet";
String fileExt	= "csv";
String completeFileName;

String data[] = {
  "This can be line 1.",
  "This line can be bmp data.: Altitude: 123m.",
  "Datalogging is fun. More so than telemetry. (Not really though)",
  "Throw in some special characters: \t this is a tab.",
  "This is a new line: \n. See?",
  "'nuf said."
};

void setup() {
	#ifdef SER_DEBUG
		// Open SerialUSB communications and wait for port to open:
		SerialUSB.begin(115200);
		while (!SerialUSB); // wait for SerialUSB port to connect. Needed for native USB port only

		SerialUSB.print("Initializing SD card...");
	#endif
	
  if (!SD.begin(sd_select)) {
		#ifdef SER_DEBUG
			SerialUSB.println("initialization failed!");
		#endif
    return;
  }
	#ifdef SER_DEBUG
		SerialUSB.println("initialization done.");
	#endif
  //completeFileName = String(fileName + "_" + String(millis()) + "." + fileExt);
  completeFileName = String(fileName + "." + fileExt);	//filename cannot be too long

	//delete any pre-existing record
  if(SD.exists(completeFileName)){
		#ifdef SER_DEBUG
			SerialUSB.println("Found " + completeFileName +". Removing it.");
    #endif
		SD.remove(completeFileName);
  }
  //Create a new file
	#ifdef SER_DEBUG
		SerialUSB.println("Creating " + completeFileName + " ...");
  #endif
	if (packetLog = SD.open(completeFileName, FILE_WRITE)) {
		#ifdef SER_DEBUG
			SerialUSB.println(completeFileName + " created.");
		#endif
	}
  else {	//die
		#ifdef SER_DEBUG
			SerialUSB.println("Failed to create " + completeFileName);
    #endif
		return;
  }
  packetLog.close();

  for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
		#ifdef SER_DEBUG
			SerialUSB.println("Iteration " + String(i));
    #endif
		//open file in append mode.
    if (packetLog = SD.open(completeFileName, FILE_WRITE)) {
			#ifdef SER_DEBUG
				SerialUSB.println("\t" + completeFileName + " opened.");
			#endif
		}
    else {	//die
			#ifdef SER_DEBUG
				SerialUSB.println("\t Failed to open " + completeFileName);
      #endif
			return;
    }

    //write a data string to the file
    packetLog.println(data[i]);
		#ifdef SER_DEBUG
			SerialUSB.println("\t Printed the line: " + data[i]);
		#endif
    packetLog.close();
  }
	#ifdef SER_DEBUG
		SerialUSB.println("Done.");
	#endif
}

void loop() {
  //wait for user to press a button
  SerialUSB.println("Press any key to read the file.");
  while(!SerialUSB.available());
  while(SerialUSB.available())
    SerialUSB.read();

  //open file in read mode.
  if (packetLog = SD.open(completeFileName, FILE_READ)) {
    SerialUSB.println("\t" + completeFileName + " opened.");
  }
  else {	//die
    SerialUSB.println("\t Failed to open " + completeFileName);
    return;
  }

  while (packetLog.available()) {
    SerialUSB.write(packetLog.read());
  }

  packetLog.close();
}
