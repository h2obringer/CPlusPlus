//*****************************************************************************************
//File: main.cc
//
//Author: Randy Obringer
//
//Date Last Modified: ~2010
//
//Description: Manipulate student course information to add/remove course information and calculate
//	a sutdent's grades.
//*****************************************************************************************


#include "student.h"
using namespace std;

int main(){

	student Randy;
	ifstream ins;
	ins.open("data.txt");
	Randy.load_from_file(ins);
	ins.close();
	if(Randy.get_PID()=="NA")
	Randy.input_student(cin);

	int choice; //menu for ease of navigation through program
	do{
		cout << "Choose 1 to insert additional class information\n";
		cout << "Choose 2 to output the data\n";
		cout << "Choose 3 to remove a course\n";
		cout << "Choose 4 to copy and show the data using the assingment operator\n";
		cout << "Choose 5 to make a local copy of student data\n";
		cout << "Choose 6 to quit the program\n";
		cin >> choice;

		switch(choice){
			case 1:
				Randy.input_course_info(cin);
				break;
			case 2:
				Randy.output_student(cout);
				break;
			case 3:
				Randy.remove_course();
				break;
			case 4:{
				student copied=Randy;
				copied.output_student(cout);
				break;}
			case 5:{
				student copy(Randy); //use of copy contructor as proof that it works
				copy.output_student(cout); //proof that it has been copied...
				break;}
			case 6:
				cout << "End of program...\n";
				break;
			default:
				cout << "This is not a valid choice. Choose again:\n";
		}
	}while(choice!=6);
	  
	Randy.write_to_file();
}
