////////////////////////////////////
//  Leni Project #3
//  runway class
//

#ifndef _RUNWAY_H
#define _RUNWAY_H


#include "air_vehicle.h"
#include <iostream>
#include <sstream>
class runway
{
	
public:
		
	runway(int id=-1);
	
	//accessor functions
	bool truck_here(){return fire_truck;};
	bool fire(){return on_fire;}
	bool open(){return is_open;};
	bool heli_can_l(){return heli_can_land;}
	int fire_time(){return fire_count;}
	int heli_time(){return heli_count;}
	int get_id(){return runway_id;}
	int get_landing_count(){return landing_count;}


	// mutator functions
	void close_runway(){ is_open = false; }
	void open_runway(){ is_open = 1;on_fire=0; }
	void set_fire(){ fire_count = 21; close_runway();on_fire=1;}
	void land_heli(){ heli_count = 2; close_runway(); }
	void set_truck(bool i){fire_truck = i;}
	void landing(){landing_count = 7;close_runway();}
	void heli_can_la(bool i){heli_can_land = i;}
	void set_heli_count(int i){heli_count = i;}
	void step();
	void operator --();
	
	//log functions
	void output(std::ostream &ous);
	void output_heli(std::ostream &ous);
	void output_fire(std::ostream &ous);
	void output_plane(std::ostream &ous);
	//overloading operators
	friend std::ostream &operator <<(std::ostream &ous,runway &run){run.output(ous);return ous;};


private:
	bool heli_can_land;
	bool on_fire;
	bool is_open;
	bool fire_truck;
	int fire_count;
	int landing_count;
	int heli_count;
	int runway_id;
	
};

#endif