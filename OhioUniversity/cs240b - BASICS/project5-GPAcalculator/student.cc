//******************************************************************************************
//File: student.cc
//Author: Randy Obringer
//Purpose: This is the implementation for the student class. Includes the bulk of what is 
//used throughout the course of the program.
//It gives all the functions that are necessary for the manipulation of student's class records
//
//Project 5
//******************************************************************************************

#include "student.h"
using namespace std;

student::student(){  //constructor-makes sure that variables are assigned a value before they
  name=PID="NA";	//are called upon somewhere in the program
  GPA=0;
  head=NULL;
}

student::~student(){  //destructor-frees memory back to the computer when the student goes
  node* rmptr;		//out of scope
  while(head!=NULL){
    rmptr=head;
    head=head->link;
    delete rmptr;
  }
}

student::student(const student& other){ //makes a local copy of the student. then goes out of 
  cout << "This is a copy" << endl;	//scope (the way it is incorporated in main.cc)
  if(other.head==NULL){
    head=NULL;
  }else{
    name=other.name;
    PID=other.PID;
    GPA=other.GPA;
    head=new node;
    head->course=other.head->course;
    head->grade=other.head->grade;
    head->hours=other.head->hours;
    node* d_ptr=head;
    node* s_ptr=other.head->link;
    while(s_ptr!=NULL){
      d_ptr->link=new node;
      d_ptr=d_ptr->link;
      d_ptr->course=s_ptr->course;
      d_ptr->grade=s_ptr->grade;
      d_ptr->hours=s_ptr->hours;
      s_ptr=s_ptr->link;
    }
    d_ptr->link=NULL;
  }
}

student& student::operator=(const student& other){ //overloaded assignment operator
  if(this==&other){
    cout << "This is a copy" << endl;
    return *this;
  }
  node* rmptr;
  while(head!=NULL){
    rmptr=head;
    head=head->link;
    delete rmptr;
  }
  if(other.head==NULL){
    head=NULL;
    return *this;
  }else{
    name=other.name;
    PID=other.PID;
    GPA=other.GPA;
    head=new node;
    head->course=other.head->course;
    head->grade=other.head->grade;
    head->hours=other.head->hours;
    node* d_ptr=head;
    node* s_ptr=other.head->link;
    while(s_ptr!=NULL){
      d_ptr->link=new node;
      d_ptr=d_ptr->link;
      d_ptr->course=s_ptr->course;
      d_ptr->grade=s_ptr->grade;
      d_ptr->hours=s_ptr->hours;
      s_ptr=s_ptr->link;
    }
    d_ptr->link=NULL;
    cout << "This is a copy" << endl;
    return *this;
  }
}

istream& student::input_student(istream& ins){ //inputs the basic information of the student
  if(ins==cin)cout << "Please enter the name of the student:\n";
  getline(ins,name);
  if(ins==cin)cout << "Please enter the PID of the student:\n";
  getline(ins,PID);
}

istream& student::input_course_info(istream& ins){ //inserts courses in correct order unless
  string temp_course;	//there is a mix between lower case and capital letters.
  string temp_grade;
  double temp_hours;
  if(ins==cin)cout << "Please enter the course abbreviation:\n";
  if(ins.peek()=='\n')ins.ignore();
  getline(ins,temp_course);
  if(ins==cin)cout << "Please enter the grade recieved in the class:\n";
  getline(ins,temp_grade);
  if(ins==cin)cout << "Please enter the credit hours the class takes:\n";
  ins >> temp_hours;
  node* aptr=head;
  node* bptr=head;
  node* cptr=head;
  if(head==NULL){
    head=new node;
    head->course=temp_course;
    head->grade=temp_grade;
    head->hours=temp_hours;
    head->link=NULL;
  }else if(temp_course<(head->course)){
    bptr=new node;
    bptr->course=temp_course;
    bptr->grade=temp_grade;
    bptr->hours=temp_hours;
    bptr->link=head;
    head=bptr;
  }else{
    while(aptr->link!=NULL){
      cptr=aptr;
      aptr=aptr->link;
    }if(temp_course<(aptr->course)){
      bptr=new node;
      bptr->course=temp_course;
      bptr->grade=temp_grade;
      bptr->hours=temp_hours;
      bptr->link=aptr;
      cptr->link=bptr;
    }else{
      bptr=new node;
      bptr->course=temp_course;
      bptr->grade=temp_grade;
      bptr->hours=temp_hours;
      bptr->link=NULL;
      aptr->link=bptr;
    } 
  }
return ins;
}

istream& operator>>(istream& in,student& temp){ //overloaded input operator
  temp.input_course_info(in);
}

ostream& student::output_student(ostream& outs){ //outputs all data. Calculation for GPA
  if(outs==cout)cout<< "Name:";	//is finally made here at this stage.
  outs << name << endl;
  if(outs==cout)cout<< "PID:";
  outs << PID << endl;
  if(outs==cout)cout<< "GPA:";
  if(outs==cout)outs << GPA_calc() << endl;
  if(outs==cout)cout << endl;
  node* print=head;
  while(print!=NULL){
    if(outs==cout)outs << "Course: ";
    outs << print->course << endl;
    if(outs==cout)outs << "Grade: ";
    outs << print->grade << endl;
    if(outs==cout)outs << "Hours: ";
    outs << print->hours << endl;
    if(outs==cout)outs << endl;
    print=print->link;
    }
  return outs;
}

ostream& operator<<(ostream& out,student& temp){ //overloaded output operator
  temp.output_student(out);
  return out;
}

void student::remove_course(){ //asks the user for a course to remove
  string target;	//if it exists it lets the user know it was deleted
  node* previous;	//if it does not exist then it will let the user know it didn't exist
  node* target_rm;
  target_rm=head;
  cout << "Please enter the course you wish to remove:" << endl;
  if(cin.peek()=='\n')
    cin.ignore();
  getline(cin,target);
  while(target_rm!=NULL&&target_rm->course!=target){
    previous=target_rm;
    target_rm=target_rm->link;
  }
  if(target_rm==head){
    head=head->link;
    delete target_rm;
    cout << target << " has been removed" << endl;
  }else if(target_rm!=NULL){
    previous->link=target_rm->link;
    delete target_rm;
    cout << target << " has been removed" << endl;
  }else cout << target << " does not exist" << endl;
}

double student::GPA_calc(){	//calculates the GPA for the total of all courses that have 
  node* GPA_ptr;		//been inputed
  double temp_grade=0.0;
  double total_grade=0.0;
  double total_hours=0.0;
  GPA_ptr=head;
  while(GPA_ptr!=NULL){
    if(GPA_ptr->grade=="A")
      temp_grade=4.0;
    if(GPA_ptr->grade=="A-")
      temp_grade=3.66;
    if(GPA_ptr->grade=="B+")
      temp_grade=3.33;
    if(GPA_ptr->grade=="B")
      temp_grade=3.0;
    if(GPA_ptr->grade=="B-")
      temp_grade=2.66;
    if(GPA_ptr->grade=="C+")
      temp_grade=2.33;
    if(GPA_ptr->grade=="C")
      temp_grade=2.0;
    if(GPA_ptr->grade=="C-")
      temp_grade=1.66;
    if(GPA_ptr->grade=="D+")
      temp_grade=1.33;
    if(GPA_ptr->grade=="D")
      temp_grade=1.0;
    if(GPA_ptr->grade=="D-")
      temp_grade=.66;
    if(GPA_ptr->grade=="F")
      temp_grade=0.0;
    total_hours += GPA_ptr->hours;
    total_grade+=(temp_grade*(GPA_ptr->hours));
    GPA_ptr=GPA_ptr->link;
  }
  GPA=(total_grade/total_hours);
  return GPA;
}

void student::write_to_file(){ //"saves" the data for use in later sessions
  ofstream outs;
  outs.open("data.txt");
  output_student(outs);
  outs.close();
}

void student::load_from_file(istream& ins){ //"loads" the data for use from previous sessions
  input_student(ins);		//uses a sentinel loop process
  string temp_course;
  string temp_grade;
  double temp_hours;
  getline(ins,temp_course);
  getline(ins,temp_grade);
  ins >> temp_hours;
  while(ins){
    if(head==NULL){
      head=new node;
      head->course=temp_course;
      head->grade=temp_grade;
      head->hours=temp_hours;
      head->link=NULL;
      ins >> temp_course;
      ins >> temp_grade;
      ins >> temp_hours;
    }else{
      node* new_ptr=head;  
      while(new_ptr->link!=NULL){
        new_ptr=new_ptr->link;
      }
      new_ptr->link=new node;
      new_ptr=new_ptr->link;
      new_ptr->course=temp_course;
      new_ptr->grade=temp_grade;
      new_ptr->hours=temp_hours;
      new_ptr->link=NULL;
      ins >> temp_course;
      ins >> temp_grade;
      ins >> temp_hours;
    }
  }
}
