#ifndef database_h
#define database_h

#include "vregistration.h"

using namespace std;

class database{
  public:
  database();
  ~database();		//Destructor - part of the "Big 3"
  database(const database& other);  //Copy constructor - part of the "Big 3"
  database& operator=(const database& other);  //Overloaded assignment operator
  void show_records(); //ouputs the entire array
  void add_record(); //allows the addition of another vehicle registration
  void find_LP(); //finds a registration by searching for a license plate number
  void resize();  //resizes the function
  void load_from_file();  //loads previously saved data
  void write_to_file();  //"saves" current session of the program for later use
  void randomDriver();  //picks a random registration from the list and outputs it to the screen
  void sortByOwner();	//sorts list in alphabetical order by owner name

  private:
  int used;  //used to keep track of the amount of registrations filling the array
  int capacity;  //used to determine how many free spots are in the array and helps determine
//when the array needs to be resized
  vregistration *r_ptr; //used for dynamic memory
};

#endif

