#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "sim.h"
#include <queue>
#include "vehicles.h"




int main (int argc, char* argv[])
{
	

	

	system("clear");
	srand(time(NULL)); //seed the random
	
	if (argc < 3) /*checks if valid paramets were passed*/ 
	std::cout<<"-- Error — simulation requires 2 parameters\n-- EX. ./a.out 10 1\n -- The first representing how many hours the simulation will run\n-- and the second sayying if airforce one will land or not  1 for yes and 0 for no\n";
	
	else /* RUNS The Simulations */ 
	sim mysim((atoi(argv[1])*60),atoi(argv[2]));
	

	

}