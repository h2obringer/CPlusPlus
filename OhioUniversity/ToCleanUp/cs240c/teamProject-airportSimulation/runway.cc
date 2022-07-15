/*
 *  runway.cc
 *  airport
 *
 *  Created by Sam Saccone on 4/28/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "runway.h"

runway::runway(int id)
{
	on_fire = false;
	is_open = true;
	fire_truck = false;
	heli_can_land =false;
	fire_count = 0;
	heli_count = 0;
	runway_id = id;
	landing_count=0;
}


void runway::step()
{
	if (on_fire && fire_truck) --fire_count;
	if ((heli_count > 0)&&heli_can_land)  --heli_count;
	if (landing_count > 0)--landing_count;
	
	if (fire_count == 0 && heli_count ==0 && landing_count ==0) {open_runway();fire_truck=0;}
		
	/*
	
	if (fire_count > 0 && fire_truck) //DECREMENT THE FIRE COUNTER
	{
		--fire_count;

		if (fire_count == 0) //IF THE FIRE IS OUT RELEASE THE FIRETRUCK
		{
			fire_truck=0;
			open_runway();
		}
	}
	
	if (heli_count >= 0&&heli_can_land) //DECREMENT THE HELICOPTER COUNTER
	{
		
		--heli_count;
		if (heli_count == 0)
		open_runway();

	}
	
	if (landing_count >= 0) //DECREMENT THE LANDING COUNT
	{
		--landing_count;
		if (landing_count == 0)
			open_runway();
	}
	
	if (fire_count > 0 || heli_count >0 || landing_count>0) //OPENS THE RUNWAY IF ALL THE COUNTERS ARE 0
	{
		close_runway();
	}
		*/
}

void runway::operator --()
{ 
	step();
	
}

void runway::output_heli(std::ostream &ous)
{
	if (heli_count >0)
	{
		ous<<"\n*** This Runway is Closed due to a Helicopter Landing";
		if (!heli_can_land)
			ous<<"\n*** The Helicopter is waiting for all runways to be clear\n";
		else
			ous<<"\n*** The Helicopter has "<<heli_count<<" MIN till landed\n";

	}
}
void runway::output_fire(std::ostream &ous)
{
	if (on_fire)
		ous<<"\n*** This Runway is ON FIRE";
	if (fire_truck && on_fire)
		ous<<"\n*** Time Till Fire Is Out "<<fire_count<<" MIN\n";
	else if (!fire_truck && on_fire)
		ous <<"\n*** No Fire Truck Is currently at this runway.. so it burns.....\n";	
}
void runway::output_plane(std::ostream &ous)
{
	if (landing_count >0)
		ous<<"\n*** An Airplane is currently landing"<<"\n*** Time Till The Airplane is landed: "<<landing_count<<" MIN\n";
}

void runway::output(std::ostream &ous)
{
	if (!is_open)
	{
		ous << "\n-------- Runway ID "<<runway_id<< " ----------\n";
		output_heli(ous);
		output_fire(ous);
		output_plane(ous);
		ous<<  "\n--------------------------------\n";
	}

}
