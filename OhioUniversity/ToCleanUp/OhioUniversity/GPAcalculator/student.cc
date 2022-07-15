//******************************************************************************************
//File: student.cc
//
//Author: Randy Obringer
//
//Date Last Modified: ~2010
//
//Description: This is the implementation for the student class.
//It gives all the functions that are necessary for the manipulation of student's class records.
//******************************************************************************************

#include "student.h"
using namespace std;

//constructor
student::student(){  
	name=PID="NA";	
	GPA=0;
	head=NULL;
}

//destructor
student::~student(){  
	node* rmptr;		
	while(head!=NULL){
		rmptr=head;
		head=head->link;
		delete rmptr;
	}
}

//copy constructor
student::student(const student& other){ 
	cout << "This is a copy" << endl;	
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

//overloaded assignment operator
student& student::operator=(const student& other){ 
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

//prompt for input of basic student information
istream& student::input_student(istream& ins){ 
	if(ins==cin)cout << "Please enter the name of the student:\n";
	getline(ins,name);
	if(ins==cin)cout << "Please enter the PID of the student:\n";
	getline(ins,PID);
}

//prompt for input of student course information
//insert courses in correct order unless there is a mix between lower case ad capital letters
istream& student::input_course_info(istream& ins){ 
	string temp_course;	
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
		}
		
		if(temp_course<(aptr->course)){
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

//overloaded input operator
istream& operator>>(istream& in,student& temp){ 
  temp.input_course_info(in);
}

//outputs all data and calculates GPA
ostream& student::output_student(ostream& outs){ 
	if(outs==cout)outs<< "Name:";	
	outs << name << endl;
	if(outs==cout)outs<< "PID:";
	outs << PID << endl;
	if(outs==cout)outs<< "GPA:";
	if(outs==cout)outs << GPA_calc() << endl;
	if(outs==cout)outs << endl;
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

//overloaded output operator
ostream& operator<<(ostream& out,student& temp){ 
	temp.output_student(out);
	return out;
}

//asks the user for a course to remove, if it exists it lets the user know it was deleted
//if it does not exist then it will let the user know it didn't exist
void student::remove_course(){ 
	string target;	
	node* previous;	
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

//calculates the GPA for the total of all courses that have been input 
double student::GPA_calc(){	
	node* GPA_ptr;		
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

//"saves" the data for use in later sessions
void student::write_to_file(){ 
	ofstream outs;
	outs.open("data.txt");
	output_student(outs);
	outs.close();
}

//"loads" the data for use from previous sessions
void student::load_from_file(istream& ins){ 
	input_student(ins);		
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
