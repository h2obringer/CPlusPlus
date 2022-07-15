//Author: Randy Obringer
//File: library.h
//Date Last Modified: ~2011
//Description: This is the header file for the library class. See library.cc for additional documentation. 
//

#ifndef library_h
#define library_h

#include "dvd.h" 

using namespace std;

class library{
	public: 
		library();
		void add_dvd();
		void delete_dvd();
		void display_library();
		void search_title();
		void sort_title();
		void sort_year();
		void sort_movie_type();
		void display_rating();
		void write_to_file();
		void load_from_file();
	private:
	    dvd data[200];	
	    int used;		//Keeps track of the overall amounts of dvd's in the collection for the
};			//entire program. Extremely important for this entire task.

#endif
