/*
 *  sim.h
 *  airport
 *
 *  Created by Sam Saccone on 4/28/10.
 *  Copyright 2010. All rights reserved.
 *
 */

#include "runway.h"
#include "vehicles.h"
#include "airport.h"
#include "log.h"

class sim
{ //.0005
	public:
	sim(int runtime=0,bool af_one = 0,int Runways=3,double plane_prob = .45,double hele_prob=.01,double fire_prob=0.0005);
	void one_step();
	void incoming_plane();
	void output();
	void crash();
	void land();
	void af_one_land();
	void run();
	void catch_runway();
	void random_events();
	void step_runways();
	void heli_land();
	void try_land(int i); 
	bool check_fire_truck();
	void check_heli_closed();
	bool check_landing();
	void log_runways();
	void save_stats();
	private:
	airport my_airport;
	double prob_of_plane;
	double prob_of_heli;
	double prob_of_fire;
	log my_log;
	int runways;
	int run_time;
	bool af_one;
	double total_people, total_dead, total_alive, total_planes,planes_landed,planes_crashed,this_time,fires,helis,wait_time;
	runway runway_array[3];
};



