#ifndef AIRPORT_H
#define AIRPORT_H

//********************************************************************************
//Author: Randy Obringer
//File: Airport.h
//Description: This is the airport file that includes the priority queue needed
//to effectively run this program.
//********************************************************************************

#include <iostream>
#include <queue>
#include <sstream>
#include "vehicles.h"
#include "log.h"

class compare_plane //overload the comparison operator for planes
{
public:
	bool operator()(airplane &a1,airplane &a2)
	{
		if (a2.get_af()) return true;
		if (a1.get_fuel() > a2.get_fuel()) return true;
		if (a1.get_fuel() == a2.get_fuel() && a1.get_fuel() > a2.get_fuel()) return true;
		if (a1.get_fuel() == a2.get_fuel() && a1.get_fuel() == a2.get_fuel() && a1.get_fuel() < a2.get_fuel()) return true;
		return false;
	}
};


class airport{
  public:
    void add_to_queue(airplane tmp);
	airplane top(){return landing_list.top();};
	void pop(){landing_list.pop();};
	bool empty(){return landing_list.empty();};
	int size(){return landing_list.size();};
	void step(int time);
	void save(); 	
  private:
	std::priority_queue<airplane, std::vector<airplane>,compare_plane> landing_list;

};

#endif
