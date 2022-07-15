#include "database.h"
using namespace std;

int main(){
database records; //declared database object that will hold vehicle registrations
database copy1; //used for making copies
records.load_from_file();  //loads the previously "saved" data

int choice; //menu for ease of navigation through program
  do{
    cout << "Choose 1 to insert an additional vehicle registration\n";
    cout << "Choose 2 to show all records\n";
    cout << "Choose 3 to sort and display the list in alphabetical order by owner\n";
    cout << "Choose 4 to find a registration by license plate number\n";
    cout << "Choose 5 to display a random registration\n";
    cout << "Choose 6 to create a copy of the list and view it using the assignment operator\n";
    cout << "Choose 7 to quit the program\n";
    cin >> choice;

    switch(choice){
    case 1:
      records.add_record(); 
      break;
    case 2:
      records.show_records();
      break;
    case 3:
      records.sortByOwner();
      break;
    case 4:
      records.find_LP();
      break;
    case 5:
      records.randomDriver();
      break;
    case 6:
      copy1 = records; //Proof that assignment operator works
      copy1.show_records();
      break;
    case 7:
      cout << "End of program...\n";
      break;
    default:
      cout << "This is not a valid choice. Choose again:\n";
    }
  }while(choice!=7);

  database data(records); //use of copy contructor as proof that it works
  data.show_records(); //proof that it has been copied...

  records.write_to_file(); //"saves" the current session of the program

  return 0;
}
