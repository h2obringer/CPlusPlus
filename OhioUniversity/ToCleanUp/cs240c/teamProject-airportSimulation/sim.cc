/*
 *  sim.cc
 *  airport
 *
 *  Created by Sam Saccone on 4/28/10.
 *  Copyright 2010  All rights reserved.
 *
 */

#include "sim.h"
#include <stdio.h>
#include <stdlib.h>

sim::sim(int runtime,bool af_one,int Runways,double plane_prob,double hele_prob,double fire_prob) //constructor of the simulation class
{
	/* Initilize all the variables */
	run_time = runtime; 
	af_one = af_one; 
	runways = Runways; 
	prob_of_plane = plane_prob; 
	prob_of_heli = hele_prob; 
	prob_of_fire =fire_prob;
	total_people = 0;
	total_dead = 0;
	total_alive = 0;
	total_planes = 0;
	planes_landed = 0;
	planes_crashed = 0;
	fires =0;
	helis =0;
	wait_time=0;

	runway_array[0] = runway(1);
	runway_array[1] = runway(2);
	runway_array[2] = runway(3);
	
	
	
	run();	
	my_log.save();
}

void sim::run() //runs the main loop for the program :)
{
	for (int i=1;i<=run_time;++i)
	{
		this_time = i;
		my_log.print_time(i);
		{
			if (i==90 && af_one) af_one_land();
			one_step();
		}
	}
	save_stats();
		my_airport.save();





	
}

void sim::save_stats() //saves the statistics for the simulation
{
	std::ofstream ous;
	ous.open("stats.txt");
	
	ous<<"\nTotal People "<<total_people;
	ous<<"\nTotal People Alive "<<total_alive;
	ous<<"\nTotal People Killed "<<total_dead;
	ous<<"\nTotal Planes  "<<total_planes;
	ous<<"\nTotal Planes Crashed "<<planes_crashed;
	ous<<"\nTotal Planes Landed "<<planes_landed;
	ous<<"\nTotal Helicopters Landed "<<helis;
	ous<<"\nAVG waiting time "<<wait_time/planes_landed;
	ous<<"\nTOTAL waiting time "<<wait_time;
	ous<<"\nStill in Queue "<<my_airport.size();
	ous<<"\nTotal Fires "<<fires<<"\n";
	ous.close();
	
}
////
//PLANE CODE
bool sim::check_landing() //checks to see if planes are still in the first 2 min of landing RETURNS FALSE IF NOT OPEN 
{
	bool flag=1;
	for (int i=0;i<runways;++i)
		if (runway_array[i].get_landing_count() >= 6)
			flag=0;
	return flag;

}

void sim::incoming_plane() //handles when a new plane is arriving at the airport
{
	try {
		airplane tmp(this_time);
		my_log>>"***** NEW INCOMING PLANE\n";
			//ADD A PLANE TO THE QUEUE 
			my_airport.add_to_queue(tmp);
		

	}
	catch (char * str) 
	{
		my_log>>"*****Plane Diverted Due to lack of passengers*****\n";
	}
}
			

void sim::crash() //crashes a plane
{
	total_people += (my_airport.top()).get_pass();
	total_dead += (my_airport.top()).get_pass();
	total_planes++;
	planes_crashed++;

}

void sim::land() //lands a plane
{
	if (my_airport.top().get_af()) my_log>>"\n---- AIRFORCE 1 LANDING ---";
	total_people += (my_airport.top()).get_pass();
	total_planes++;
	total_alive +=(my_airport.top()).get_pass();
	wait_time +=  this_time-(my_airport.top()).get_created();
	planes_landed++;

}

void sim::try_land(int i) //lands a plane
{
	//((my_airport.top().get_fuel() - (this_time - my_airport.top().get_created()))
	while (my_airport.top().get_fuel() < 1 && !my_airport.empty() )
	{
		crash();
		my_log >> "\n***** PLANE CRASHED\n";
		my_log.log_it(my_airport.top());
		my_airport.pop();

	}
	
	if(!my_airport.empty())
	{
		land();
	runway_array[i].landing();
	my_log >> "\n***** PLANE LANDING\n";
	}

}

void sim::log_runways() //writes out all the logs for the runway
{
	for (int i=0;i<runways;++i)
	my_log.log_runway(runway_array[i]);
}


void sim::step_runways() //steps the runways through a single cycle
{

	for (int i=0;i<runways;++i)
	{
		if (!runway_array[i].open()||!check_landing()) //if the runway is not open
		{
			check_heli_closed();
			if (runway_array[i].fire() && check_fire_truck()) { runway_array[i].set_truck(1);} 
			--runway_array[i];

			
		}
		if (!my_airport.empty()&&runway_array[i].open()&&check_landing())
		{
			try_land(i);
			if (!my_airport.empty())
			my_airport.pop();
		}

	}
	int time = runway_array[0].heli_time();
	for (int i=0;i<runways;++i)
		runway_array[i].set_heli_count(time);
	check_heli_closed();
}
 
////
//HEli CODE

void sim::heli_land() //lands a helicopter
{
	helis++;
	my_log>>"HELICOPTER LANDING\n";
	for (int i=0;i<runways;++i)
	{
		runway_array[i].land_heli();
	}
	

	
}

void sim::random_events() //handles the generation of random events 
{
	if ((rand()/(double)RAND_MAX )<=prob_of_plane)
	{
		incoming_plane();
	}
	if ((rand()/(double)RAND_MAX )<=prob_of_heli)
	{
		heli_land();
	}
	if ((rand()/(double)RAND_MAX )<=prob_of_fire)
	{
		catch_runway();	
	}	
}

void sim::one_step() //runs the functions for one min of the simulation
{
	random_events();
	step_runways();
	log_runways();
	my_airport.step(this_time);
	
}

////
//RUNWAY CODE

bool sim::check_fire_truck() //checks if the firetruck is currently avalible if it RETURNS TRUE
{
	bool firet = 1;
	for (int ii=0;ii<runways;++ii)   //checks to see if the fire truck is currently tending another fire
		if (runway_array[ii].truck_here())
			firet = 0;
	return firet;
}

void sim::check_heli_closed() //checks if all the runways are empty and the helicopter can land and start its countdown
{
	bool flag = 1;
	for (int ii=0;ii<runways;++ii)   
		if (runway_array[ii].get_landing_count()>0) //checks that all the planes have landed 
			flag = 0;
	for (int i=0;i<runways;++i)   //sets the status of all the runways to knwo if the helicopter can start its landing seq
		runway_array[i].heli_can_la(flag);
	
}


void sim::catch_runway() //lights a runway on fire
{
	fires++;
	int i =0;
	while (runway_array[i].fire())i++;
	if (i == runways) my_log>>"ALL RUNWAYS ALREADY ON FIRE\n";
	else
	{
		my_log >> "RUNWAY FIRE " ;
		runway_array[i].set_fire();
	}
	
}


void sim::af_one_land() //handles the landing of airforce one
{
	my_log>>"**Air Force One** \n";
	airplane tmp(this_time);
	tmp.set_af(1);
	my_airport.add_to_queue(tmp);
}