/*
 * packet.h
 */

#ifndef packet_h
#define packet_h

enum op_state {
	boot, idle, launch_detect, deploy
};
const String op_state_string_lut[] = {
	"Boot", "Idle", "Launch detect", "Deploy"
};

class packet {
  public:
	packet(const int team_id);
	~packet(void);
	
  int team_id;			// the assigned team identification
	volatile int mission_time;	//the time since initial power up in seconds
	volatile int packet_count;	// the count of transmitted packets, which is to be maintained through processor reset.
	volatile float altitude;	// the altitude in units of meters and must be relative to ground level. The resolution must be 0.1 meters.
	volatile float pressure;	//the measurement of atmospheric pressure in units of pascals. The resolution must be 0.1 pascals.
	volatile float temperature;	// the sensed temperature in degrees C with one tenth of a degree resolution.
	volatile float voltage;		//the voltage of the CanSat power bus. The resolution must be 0.01 volts.
	String gps_time_utc;		// the time generated by the GPS receiver. The time must be reported in UTC and have a resolution of a second. UTC Format: 2013-10-22T01:37:56+05:30
	volatile float gps_lattitude;	//the latitude generated by the GPS receiver in decimal degrees with a resolution of 0.0001 degrees.
	volatile float gps_longitude;	//the longitude generated by the GPS receiver in decimal degrees with a resolution of 0.0001 degrees.
	volatile float gps_altitude;	//the altitude generated by the GPS receiver in meters above mean sea level with a resolution of 0.1 meters.
	volatile int gps_sats;		// the number of GPS satellites being tracked by the GPS receiver. This must be an integer number.
	volatile int pitch;			// the tilt angle in the pitch axis in degrees. The resolution must be 1 degree.
	volatile int roll;			// the tilt angle of the roll axis in degrees. The resolution must be 1 degree.
	volatile int blade_spin_rate;	// the rate the auto-gyro blades spin relative to the science payload. The units must be in revolutions per minute (rpm). The resolution must be 1 rpm.
	volatile op_state software_state;			// the operating state of the software. (boot, idle, launch detect, deploy, etc.)
	volatile int bonus_direction;	// the direction the camera is pointed relative to earth’s magnetic north specified in degrees.
	
	String toString();			//returns a csv string of all the data fields.
	
};

#endif // packet_h
