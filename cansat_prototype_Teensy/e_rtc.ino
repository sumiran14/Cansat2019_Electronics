//Variable to store startTime of mission
uint32_t startTime = 1546800011;	//Monday, January 7, 2019 12:09:02 AM GMT+05:30
/*
 * Function : To initialize the rtc object that was created in cansat_prototype_1.ino
 *             It set the epoch time to 0;
 */
/*
getEpoch() function returns the UNIX epoch time, ie the number of seconds since Jan 1 1970, provided it has been set accurately first.
So we will be using that as a permanent millis() function.
*/

void resetMissionTime(){
  DateTime now = rtc.now();
	startTime = now.unixtime();
}
//Returns the mission time: i.e. subtraction of "current unix time" and program's "startTime"
uint32_t getMissionTime(){
  DateTime now = rtc.now();
  return (now.unixtime() - startTime);
}

inline String getRTCDate(){
  DateTime now = rtc.now();
  return (String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()));
}

inline String getRTCTime(){
  DateTime now = rtc.now();
  return (String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()));
}

String getRTCDateTime(){	//UTC
  DateTime now = rtc.now();
	String YYYY = String("20" + twoDigits(now.year()));
	String MM 	= twoDigits(now.month());
	String DD 	= twoDigits(now.day());
	String HH 	= twoDigits(now.hour());
	String mm 	= twoDigits(now.minute());
	String SS 	= twoDigits(now.second());
	String TZ 	= "+5:30";	//IST
	
	return String(YYYY+"-"+MM+"-"+DD+"T"+HH+":"+mm+":"+SS+TZ);
}

String twoDigits(int x){
	String s = "";
	if(x<10)
		s = "0";
	return String(s + String(x));
}
