//Author: Randy Obringer
//File: library.cc
//Date Last Modified: ~2011
//Description: This is the implementation for the library class.
//It gives all the necessary functions for sorting and searching for
//certain "dvd's" (Arrays)
//
//

#include "library.h"
#include "dvd.h"
using namespace std;

//constructor
library::library(){ 
  used=0;
}

//adds dvds to library
void library::add_dvd(){ 
	if(cin.peek()=='\n'){  
		cin.ignore();
	}
	cin >> data[used];
	used++;
}

//load the library from file
void library::load_from_file(){ 
	ifstream ins;                 
	ins.open("data.txt"); 
	if(!ins.eof()){
		dvd temp;
		ins>>temp;    
		while(ins){ 
			data[used]=temp; 
			used++;
			ins>>temp;
		}
	}
	ins.close();  
}

//Display all dvds in the library in their current order
void library::display_library(){    
	if(used==0){                      
		cout << "There is no DVD data added yet.\n";  
		cout << "Add DVD's and try again.\n";
		cout << endl;
	}else{
		for(int i=0;i<used;i++){
			cout << data[i];
		}
	}
}

//write the program data to file called data.txt
void library::write_to_file(){      
	ofstream outs;                      
	outs.open("data.txt");
	for(int i=0;i<used;i++){
		outs << data[i];
	}
}

//search for and display data on a certain dvd.
void library::search_title(){       
	string title_to_find;             
	cout << "What movie are you searching for?\n";  
	if(cin.peek()=='\n'){
		cin.ignore();
	}
	getline(cin,title_to_find);
	int i=0;
	while(i<used){
		if(data[i].get_title()==title_to_find){
			cout << data[i];
		}
		i++;
	}
}



//delete a dvd from the library collection
void library::delete_dvd(){	
	string title_to_find;			
	cout << "What movie do you wish to delete?\n";  
	if(cin.peek()=='\n'){
		cin.ignore();
	}
	getline(cin,title_to_find);
	int i=0;
	while(i<used){
		if(data[i].get_title()==title_to_find){
			cout <<  title_to_find << " has been removed.\n";
			break;
		}
		i++;
	}
	data[i]=data[used-1];
	used--;
	display_library();
}

//allow the user to sort the collection of dvds into alphabetical order.
//	show the library afterwards
void library::sort_title(){	
	int small_spot;			
	dvd temp;				
	for(int i=0;i<used-1;i++){		
		small_spot=i;
		for(int j=i+1;j<used;j++){
			if(data[j].get_title()<data[small_spot].get_title()){
				small_spot=j;
			}
		}
		temp=data[small_spot];
		data[small_spot]=data[i];
		data[i]=temp;
	}
	display_library();
}

//allow the user to sort the collection of dvds by year. Display the results afterward.
void library::sort_year(){		 
	int small_spot;
	dvd temp;	
	for(int i=0;i<used-1;i++){
		small_spot=i;
		for(int j=i+1;j<used;j++){
			if(data[j].get_year()<data[small_spot].get_year()){
				small_spot=j;
			}
		}
		temp=data[small_spot];
		data[small_spot]=data[i];
		data[i]=temp;
	}
	display_library();
}

//allow the user to sort the collection of dvds into alphabetical order by movie type.
//	display the collection afterwards.
void library::sort_movie_type(){
	int small_spot;	
	dvd temp;	
	for(int i=0;i<used-1;i++){
		small_spot=i;
		for(int j=0;j<used;j++){
			if(data[j].get_movie_type()<data[small_spot].get_movie_type()){
				small_spot=j;
			}
		}
		temp=data[small_spot];
		data[small_spot]=data[i];
		data[i]=temp;
	}
	display_library();
}

//allow the user to display all the movies of a given rating.
void library::display_rating(){
	string rating_to_display;
	cout << "Search and display the movies for which rating?\n";
	if(cin.peek()=='\n'){
		cin.ignore();
	}
	getline(cin,rating_to_display);
	int i=0;
	while(i<used){
		if(data[i].get_rating()==rating_to_display){
			cout << data[i];
		}
		i++;
	}
}
