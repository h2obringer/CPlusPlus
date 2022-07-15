/*
 *  air_vehicle.h
 *  airport
 *
 *  Created by Sam Saccone on 4/25/10.
 *  Copyright 2010. All rights reserved.
 *
 */


//*** time decrement is_air_force_one */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef _AIRVEH_
#define _AIRVEH_
class air_vehicle //holds the base vehicle information 
{
	public:
	
	//default constructor
	air_vehicle(int f_left = 0,int pass =0,int t_landed =-1,int Runway=-1,bool Crashed =0){fuel_left = f_left;passengers = pass;landed_at = t_landed;landed=0;runway = Runway;crashed = Crashed;wait_time=0;};
	
	//accessor functions
	int get_created(){return created_at;}
	int get_fuel(){return fuel_left;};
	int get_pass(){return passengers;};
	int get_landing_time(){return landed_at;};
	int get_runway(){return runway;};
	bool get_wait_time(){return wait_time;};

	bool get_landed(){return landed;};
	bool get_crashed(){return crashed;};
	bool get_af(){return af_one;};
	
	//mutator functions
	void set_landed_at(int time){landed_at = time;};
	void set_crashed(bool i){crashed = i;};
	void set_runway(int i){runway = i;};
	void set_fuel(int fuel){fuel_left = fuel;};
	void set_passengers(int pass){passengers = pass;};
	void set_landed(bool l){landed =l;};
	void set_af(bool i){af_one = i;};
	void set_wait_time(int i){wait_time=i;};
	//output
	virtual void output(std::ostream &ous)
	{
	 ous<<"Fuel Left: "<<fuel_left<<" min\n"<<"Passengers: "<<passengers<<" people\n";
	 if(landed)ous<<"Landed at: "<<landed_at<<" Min\n\n";
	 else ous<<"Not Landed Yet\n";
	 if (runway != -1) std::cout<<"Assigned to Runway "<<runway<<"\n";
		if (crashed== 1) std::cout<<"Plane Has Crashed\n";
	};
		 
	
	//operator
	void operator -- (){ --fuel_left;};
	friend bool operator < (air_vehicle &v1,air_vehicle &v2){ return v1.get_fuel() < v2.get_fuel();};
	friend bool operator > (air_vehicle &v1,air_vehicle &v2){ return v1.get_fuel() > v2.get_fuel();};
	friend std::ostream& operator <<(std::ostream &ous,air_vehicle &veh){veh.output(ous);return ous;};

	
	protected:
	int fuel_left,passengers,landed_at,runway,created_at,wait_time;
	bool landed;
	bool crashed;
	bool af_one;

};




#endif

