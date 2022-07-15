/*
 *  vehicles.h
 *  airport
 *
 *  Created by Sam Saccone on 4/25/10.
 *  Copyright 2010  All rights reserved.
 *
 */
#include <iostream>

#include "air_vehicle.h"
#ifndef _VEH_
#define _VEH_

class airplane:public air_vehicle //airplane vehicle type
{
public:
	airplane(int c_at,int fuel=rand() % 51 + 5,int pass =rand() % 175 + 0):air_vehicle(fuel,pass){ if (passengers<5)throw "Not enough Passengers";created_at = c_at;af_one=0;};
	void output(std::ostream &ous){
		ous << "-- Airplane --\nCreated at: "<<"HOUR "<<created_at/60<<" MIN "<<(created_at - (created_at/60 * 60))<<" Is AF_ONE "<<af_one <<"\n"<<" Wait Time "<<wait_time<<"\n";air_vehicle::output(ous);};
};




class helicopter:public air_vehicle //helicopter vehicle type
{
public:
	helicopter(int fuel=999,int pass =rand() % 6):air_vehicle(fuel,pass){ ;};
	void output(std::ostream &ous){ous << "-- Helicopter --\n";air_vehicle::output(ous);};
};

#endif