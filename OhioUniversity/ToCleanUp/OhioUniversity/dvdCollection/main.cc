//Author: Randy Obringer
//File: main.cc
//Date Last Modified: ~2011
//Description: This is the main file that utilizes all the functions given by the dvd and
//	library classes. It provides a nice menu for the user to pick amongst many options that
//	can be useful for finding any dvd in a collection as well as keeps them organized.

#include "library.h"
using namespace std;

int main(){
	library library1;
	library1.load_from_file();

	int choice;
	do{
		cout << "Choose 1 to insert an additional movie\n";
		cout << "Choose 2 to remove a movie that has become lost or destroyed\n";
		cout << "Choose 3 to display all the movies\n";
		cout << "Choose 4 to display all the movies of a certain rating\n";
		cout << "Choose 5 to search for a movie by title\n";
		cout << "Choose 6 to sort and display all movies alphabetically by title\n";
		cout << "Choose 7 to sort and display all movies by the year made\n";
		cout << "Choose 8 to quit the program\n";
		cin >> choice;

		switch(choice){
		case 1:
			library1.add_dvd();
			break;
		case 2:
			library1.delete_dvd();
			break;
		case 3:
			library1.display_library();
			break;
		case 4:
			library1.display_rating();
			break;
		case 5:
			library1.search_title();
			break;
		case 6:
			library1.sort_title();
			break;
		case 7:
			library1.sort_year();
			break;
		case 8:
			cout << "End of program...\n";
			break;
		default:
			cout << "This is not a valid choice. Choose again:\n";
		}
	}while(choice!=8);

	library1.write_to_file();
	return 0;
}
