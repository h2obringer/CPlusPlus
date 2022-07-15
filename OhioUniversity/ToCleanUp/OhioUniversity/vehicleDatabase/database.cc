/*
* Author: Randal Obringer
*
* Description: database class. Essentially implements our own vector.
*
* Date Last Modified: ~2009
*/
#include "database.h"
using namespace std;

//Constructor
database::database(){	
	used=0;
	capacity=10;
	r_ptr=new vregistration[capacity];
}

//Destructor - part of the "Big 3" - needed so we can free up memory after object goes out of scope
database::~database(){	
	delete [] r_ptr;
	cout << "I'm meltingggg!" << endl;
}

//copy constructor - part of the "Big 3" - needed to correctly copy over the dynamic array
database::database(const database& other){  
	capacity=other.capacity;
	used=other.used;
	r_ptr = new vregistration[capacity];
	for(int i=0; i<used; i++){
		r_ptr[i]=other.r_ptr[i];
	}
}

//Overloaded Assignment operator makes sure that self assignment works 
database& database::operator=(const database& other){	
	if(this==&other) return *this;
	delete [] r_ptr;
	capacity=other.capacity;		
	used=other.used;
	r_ptr = new vregistration[capacity];  //makes sure that the new object can be changed without
	for(int i=0;i<used;i++){		//making changes to the other object
		r_ptr[i]=other.r_ptr[i];
	}
	return *this;
}

//Allows the user to add a registration using dynamic memory
void database::add_record(){	
	if(used==capacity){
		resize();
	}
	cin >> r_ptr[used];
	used++;
}

//Shows the list of registrations created using dynamic memory
void database::show_records(){	
	if(used==0){
		cout << "There aren't any records. Please try entering some in and try again.\n";
		cout << endl;
	}else{
		for(int i=0;i<used;i++){
			cout << r_ptr[i];
		}
	}
}

void database::sortByOwner(){
	int small_spot;			//Sorts collection of registrations into 
	vregistration temp;			//alphabetical order. It then utilizes show_records 
	for(int i=0;i<used-1;i++){		//to show the ordering that has been done.
		small_spot=i;
		for(int j=i+1;j<used;j++){
			if(r_ptr[j].get_owner()<r_ptr[small_spot].get_owner()){
				small_spot=j;
			}
		}
		temp=r_ptr[small_spot];
		r_ptr[small_spot]=r_ptr[i];
		r_ptr[i]=temp;
	}
	show_records();
}

//This is a search through dynamic memory for the desired license plate number
void database::find_LP(){	
	string LP_to_find;
	cout << "What is the vehicle license number you are searching for?\n"; 
	if(cin.peek()=='\n'){
		cin.ignore();
	}
	getline(cin,LP_to_find);
	int i=0;
	while(i<used){
		if(r_ptr[i].get_license_plate()==LP_to_find){
			cout << r_ptr[i];
		}
		i++;
	}
}

void database::resize(){	//This is the most important piece of this project. It resizes
	vregistration *tmp_ptr;	//the array that is being used by creating a bigger array and
	tmp_ptr=new vregistration[capacity+10];  //then copying the old array into it. It then deletes
	for(int i=0;i<used;i++){	//the old array (freeing the memory back to freestore)
		tmp_ptr[i]=r_ptr[i];
	}
	delete [] r_ptr;
	r_ptr=tmp_ptr;
	capacity=capacity+10;
	cout << "I have been resized!!!" << endl;
}

//Allows the program to access data saved to file from previous usage of the program
void database::load_from_file(){ 
	ifstream ins;                 
	ins.open("data.txt"); 
	if(!ins.eof()){
		vregistration temp;
		ins>>temp;    
		while(ins){ 
			r_ptr[used]=temp; 
			used++;
			if(used==capacity){
				resize();
			}
			ins>>temp;
		}
	}
	ins.close();  
}

//When the program closes this function writes all the current created data to a file called "data.txt".
void database::write_to_file(){       
  ofstream outs;
  outs.open("data.txt");
  for(int i=0;i<used;i++){
    outs << r_ptr[i];
  }
}

void database::randomDriver(){	//First use of a randomizing function in cs240b
	time_t t;			//It seeds the rand function with the time so that 
	srand(time(&t));		//it will be completely random every time given that the
	long int random=rand();	//function isn't called twice in the same second
	long int index=random%used;	//(which is pretty hard to do anyways)
	for(int i=0;i<used;i++){
		if(i==index){
			cout << r_ptr[i] << endl;
		}
	}
}
