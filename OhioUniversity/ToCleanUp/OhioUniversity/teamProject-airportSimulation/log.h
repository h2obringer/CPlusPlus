/*
 *  log.h
 *  airport
 *
 *  Created by Sam Saccone on 5/2/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "air_vehicle.h"
#include "runway.h"
#include "airport.h"


#include <sstream>
#include <fstream>
#include <string>
#ifndef _MYLOG_
#define _MYLOG_
class log
{
	public:
	log();
	void print_time(int min);
	void save();
	void log_it(airplane tmp){my_log << tmp;}
	void log_runway(runway &tmp){my_log << tmp;}
	//void log_queue(airport &tmp){my_log << tmp;}


	void operator >> (std::string ous) {my_log<<ous;}

	private:
	std::string name;
	std::stringstream my_log;
	

};

#endif

