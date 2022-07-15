//*****************************************************************
//Author: Randy Obringer
//File: airport.cc
//Description: Writes airplane data to a string stream so that it
//can be added to the log at the end of the whole program.
//*****************************************************************

#include "airport.h"

void airport::add_to_queue(airplane tmp)
{
	landing_list.push(tmp);
}

void airport::save() 
{
	std::ofstream ous;
	ous.open("still_in_q.txt");
	while (!landing_list.empty())
	{
		airplane tmp = landing_list.top();
		ous<< tmp;
		landing_list.pop();
	}
	ous.close();
}

void airport::step(int time) //reprioritzes the queue 
{
	std::priority_queue<airplane, std::vector<airplane>,compare_plane> landing_list2;
	while (!landing_list.empty())
	{
		airplane tmp(landing_list.top());
		tmp.set_wait_time( ((time - tmp.get_created())));
		tmp.set_fuel(tmp.get_fuel() - tmp.get_wait_time());
		landing_list2.push(tmp);
		landing_list.pop();
	}
	
	while (!landing_list2.empty())
	{
		landing_list.push(landing_list2.top());
		landing_list2.pop();

	}


}