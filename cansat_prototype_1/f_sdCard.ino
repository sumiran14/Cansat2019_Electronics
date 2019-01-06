String packetFileName = "packets";
String packetFileExt	= "csv";
String completePacketFileName;

String missionFileName = "mission";
String missionFileExt	= "log";
String completeMissionFileName;

String timeStamp = "2013-10-22T01:37:56+05:30";	//UTC Format: 1994-11-05T08:15:30-05:00 corresponds to November 5, 1994, 8:15:30 am, US Eastern Standard Time.

void initSD(){
	/*
	Sets up the SD card and creates mission.log and packets.csv
	*/
	
	//----------Setting up sd card-----------//
	#ifdef SER_DEBUG
		Serial.print("Initializing SD card...");
	#endif
	
  if (!SD.begin(SD_SELECT)) {
		#ifdef SER_DEBUG
			Serial.println("initialization failed!");
		#endif
    return;
  }
	#ifdef SER_DEBUG
		Serial.println("initialization done.");
	#endif
	
	packetLog		= newFile(packetFileName, packetFileExt);
	missionLog	= newFile(missionFileName, missionFileExt); 
	
}

File newFile(String fileName, String fileExt){
	/*
	Creates and sets up a new file.
	*/
	
	File tempFile;
 //completeFileName = String(fileName + "_" + String(millis()) + "." + fileExt);
  String completeFileName = String(fileName + "." + fileExt);	//filename cannot be too long

	//delete any pre-existing record
  if(SD.exists(completeFileName)){
		#ifdef SER_DEBUG
			Serial.println("Found " + completeFileName +". Removing it.");
    #endif
		SD.remove(completeFileName);
  }
  //Create a new file
	#ifdef SER_DEBUG
		Serial.println("Creating " + completeFileName + " ...");
  #endif
	if (tempFile = SD.open(completeFileName, FILE_WRITE)) {
		#ifdef SER_DEBUG
			Serial.println(completeFileName + " created.");
		#endif
	}
  else {	//die
		#ifdef SER_DEBUG
			Serial.println("Failed to create " + completeFileName);
    #endif
		return *(new File());  //return an empty file object
  }
  tempFile.close();	
	return (tempFile);
}

boolean logEvent(const String text){
	/*
	Safely stores the text to mission.log with time stamp
	*/
	return safe_println(&missionLog, String(getTimeStamp() + "\t" + text));
}

boolean safe_print(File* file_ptr, const String text){
	/*
		Ensures no two files are opened at the same time, and data is saved to SD card
		Doesn't implement file locking, or stop interrupts.
	*/
  //open file in read mode.
  if (!SD.open(file_ptr->name(), FILE_WRITE)) {
		#ifdef SER_DEBUG		//die
			Serial.println("\t Failed to open " + String(file_ptr->name()));
		#endif
    return false;
  }
	file_ptr->print(text);
	#ifdef SER_DEBUG
		Serial.println("\t Printed the line: " + text);
	#endif
  file_ptr->close();	
	return true;
}

boolean safe_println(File* file_ptr, const String text){
	return safe_print(file_ptr, String(text + "\n"));
}

boolean safe_print(const String filename, const String text){
	File file =  SD.open(filename, FILE_READ);
	return safe_print(&file, text);
}

boolean safe_println(const String filename, const String text){
	File file =  SD.open(filename, FILE_READ);
	return safe_println(&file, text);
}

void readFile(File* file_ptr){
	
	String completeFileName = String(file_ptr->name());
	//Check if the file eists
	if(!SD.exists(completeFileName)){
		#ifdef SER_DEBUG
			Serial.println("\t" + completeFileName + " Doesn't exist");
		#endif
		return;	//die
	}
	
  //open file in read mode.
  if (SD.open(completeFileName, FILE_READ)) {
		uint32_t size =  file_ptr->size();
		#ifdef SER_DEBUG
			Serial.println(completeFileName + "\t Size: " + String(size) + " Bytes");
		#endif
  }
  else {	//die
		#ifdef SER_DEBUG
			Serial.println("\t Failed to open " + completeFileName);
		#endif
    return;
  }

  while (file_ptr->available()) {
		#ifdef SER_DEBUG
			Serial.write(file_ptr->read());
		#endif
  }
	
  file_ptr->close();	
}

void readFile(const String filename){
	File file =  SD.open(filename, FILE_READ);
	readFile(&file);
	//call file destructor
}

//to be updated with time from RTC
String getTimeStamp(){
	return timeStamp;
}
