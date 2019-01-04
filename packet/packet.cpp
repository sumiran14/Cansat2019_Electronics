#include <Arduino.h>
#include "packet.h"

//constructor
packet::packet(const int team_id){
	this->team_id = team_id;
	this->mission_time = 0;
	this->packet_count = 0;
	this->altitude = 0;
	this->pressure;
	this->temperature;
	this->voltage;
	this->gps_time_utc;
	this->gps_lattitude;
	this->gps_longitude;
	this->gps_altitude;
	this->gps_sats;
	this->pitch;
	this->roll;
	this->blade_spin_rate;
	this->software_state = boot;
	this->bonus_direction;
}

String packet::toString(){
	String csv = String( 
	  String(this->team_id) + "," +
		String(this->mission_time) + "," +
		String(this->packet_count) + "," +
		String(this->altitude) + "," +
		String(this->pressure) + "," +
		String(this->temperature) + "," +
		String(this->voltage) + "," +
		gps_tims_utc + "," +
		String(this->gps_lattitude) + "," +
		String(this->gps_longitude) + "," +
		String(this->gps_altitude) + "," +
		String(this->gps_sats) + "," +
		String(this->pitch) + "," +
		String(this->roll) + "," +
		String(this->blade_spin_rate) + "," +
		op_state_string_lut[this->software_state] + "," +
		String(this->bonus_direction)
		);
    return csv;
}
