/*
 *  log.cc
 *  airport
 *
 *  Created by Sam Saccone on 5/2/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "log.h"

log::log() { ;}

void log::print_time(int min) //prints the time of the current iteration of the simulation
{
	my_log<<"\n\n----------- HOUR "<<min/60<<" MIN "<<min - (min/60 * 60)<<" -----------\n\n";
}

void log::save() //saves the logfile
{
	std::ofstream ous;
	ous.open("log.txt");
	ous << my_log.str();
	ous.close();
}



