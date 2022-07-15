//Author: Randy Obringer
//
//File: library.cc
//Description: This is the implementation for the library class.
//It gives all the necessary functions for sorting and searching for
//certain "dvd's" (Arrays)
//
//

#include "library.h"
#include "dvd.h"
using namespace std;

library::library(){ //constructor function
  used=0;
}

void library::add_dvd(){ //used the switch statement in main.cc 
  if(cin.peek()=='\n'){  //to add dvd's to the collection
    cin.ignore();
  }
  cin >> data[used];
  used++;
}
 
void library::load_from_file(){ //Allows the program to access data saved to file
  ifstream ins;                 //from previous usage of the program
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


void library::display_library(){    //Used in main.cc as well as utilized in other library
  if(used==0){                      //functions to display all the current dvd's in their 
    cout << "There is no DVD data added yet.\n"; //current order in the program. 
    cout << "Add DVD's and try again.\n";
    cout << endl;
  }
  else
    for(int i=0;i<used;i++)
      cout << data[i];
}


void library::write_to_file(){      //When the program closes this function writes all the 
ofstream outs;                      //current created data to a file called "data.txt".
outs.open("data.txt");
  for(int i=0;i<used;i++){
    outs << data[i];
  }
}

void library::search_title(){       //Used in main.cc to allow the user to search and display
  string title_to_find;             //the data on a certain dvd. Useful when the collection of
  cout << "What movie are you searching for?\n";  //dvd's has become quite substantial
  if(cin.peek()=='\n')
    cin.ignore();
  getline(cin,title_to_find);
  int i=0;
  while(i<used){
    if(data[i].get_title()==title_to_find){
      cout << data[i];
    }
    i++;
  }
}




void library::delete_dvd(){		//used in main.cc to allow the user to delete a dvd
  string title_to_find;			//from the collection. Useful when data on a dvd has
  cout << "What movie do you wish to delete?\n";  //become lost or broken
  if(cin.peek()=='\n')
    cin.ignore();
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

void library::sort_title(){		//used in main.cc to allow the user to sort the 
  int small_spot;			//collection of dvd's into alphabetical order.
  dvd temp;				//It then utilizes display_library() to show the
  for(int i=0;i<used-1;i++){		//ordering that has been done.
    small_spot=i;
    for(int j=i+1;j<used;j++){
      if(data[j].get_title()<data[small_spot].get_title())
	small_spot=j;
    }
    temp=data[small_spot];
    data[small_spot]=data[i];
    data[i]=temp;
  }
  display_library();
}

void library::sort_year(){		//Used in main.cc and allows the user to sort the 
  int small_spot;			//collection of dvd's by year. It then utilizes
  dvd temp;				//display_library() to show the ordering that has
  for(int i=0;i<used-1;i++){		//been done.
    small_spot=i;
    for(int j=i+1;j<used;j++){
      if(data[j].get_year()<data[small_spot].get_year())
	small_spot=j;
    }
    temp=data[small_spot];
    data[small_spot]=data[i];
    data[i]=temp;
  }
  display_library();
}

void library::sort_movie_type(){	//Used by main.cc and allows the user to sort the 
  int small_spot;			//collection of dvd's into alphabetical order by movie
  dvd temp;				//type. It then utilizes display_library() to show
  for(int i=0;i<used-1;i++){		//the ordering that has been done.
    small_spot=i;
    for(int j=0;j<used;j++){
      if(data[j].get_movie_type()<data[small_spot].get_movie_type())
	small_spot=j;
    }
    temp=data[small_spot];
    data[small_spot]=data[i];
    data[i]=temp;
  }
  display_library();
}

void library::display_rating(){		//Used in main.cc and allows the user to display
  string rating_to_display;		//all the movies of a given rating. It utilizes
  cout << "Search and display the movies for which rating?\n"; //display_library() to do
  if(cin.peek()=='\n')			//this. Helpful when searching for films appropriate
    cin.ignore();			//for a given audience.
  getline(cin,rating_to_display);
  int i=0;
  while(i<used){
    if(data[i].get_rating()==rating_to_display){
      cout << data[i];
    }
    i++;
  }
}
