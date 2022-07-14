/*Author: Randal Obringer
* Description: Parse input and output the closest defibrillator given a longitude and lattitude.
* Date Last Modified: 8/15/2016
* 
* Difficulty: Easy
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Problem Statement: The city of Montpellier has equipped its streets with defibrillators to help 
*	save victims of cardiac arrests. The data corresponding to the position of all defibrillators 
*	is available online. Based on the data we provide in the tests, write a program that will allow 
*	users to find the defibrillator nearest to their location using their mobile phone. 
*	Rules:
*		The input data you require for your program is provided in text format.
*		This data is comprised of lines, each of which represents a defibrillator. 
*		Each defibrillator is represented by the following fields:
*		    A number identifying the defibrillator
*			Name
*			Address
*			Contact Phone number
*			Longitude (degrees)
*			Latitude (degrees)
*		These fields are separated by a semicolon (;).
*		Beware: the decimal numbers use the comma (,) as decimal separator. Remember to turn the 
*			comma (,) into dot (.) if necessary in order to use the data in your program.
*	DISTANCE
*		The distance d between two points A and B will be calculated using the following formula: 
*			x = (longitudeB - longitudeA)* cos(latitudeA+latitudeB/2)
*			y =(latitudeB - latitudeA)
*			d = sqrt(x^2 + y^2) *6371
*		Note: In this formula, the latitudes and longitudes are expressed in radians. 6371 corresponds 
*			to the radius of the earth in km. The program will display the name of the defibrillator 
*			located the closest to the user’s position. This position is given as input to the program.
*	Game Input:
*		Line 1: User's longitude (in degrees)
*		Line 2: User's latitude (in degrees)
*		Line 3: The number N of defibrillators located in the streets of Montpellier
*		N next lines: a description of each defibrillator
*	Output: The name of the defibrillator located the closest to the user’s position.
*	Constraints: 0 < N < 10000
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <iomanip>

using namespace std;

struct Defibrillator{
    string numID;
    string name;
    string address;
    string phone;
    double longitude;
    double latitude;
};

double calcDistance(double lonA,double lonB,double latA,double latB){    
    double x = (lonB-lonA)*cos((latA+latB)/2);
    double y = latB - latA;
    return ( sqrt( (x*x) + (y*y) ) * 6371.0);
}

//utility function
void replaceChar(string& modifyMe,char replaceMe,char replacement){
    for(int i=0;i<modifyMe.size();i++){
        if(modifyMe[i]==replaceMe){
            modifyMe[i]=replacement;
        }
    }
}

//utility function
void replaceChar(string& modifyMe){
    replaceChar(modifyMe,',','.');
}

Defibrillator parseInput(string& input){
    stringstream ss(input);
    Defibrillator temp;
    string tempLL; //for lat/lon
    getline(ss, temp.numID,';');
    getline(ss, temp.name,';');
    getline(ss, temp.address,';');
    getline(ss, temp.phone,';');
    getline(ss, tempLL,';');
    replaceChar(tempLL);
    temp.longitude=stod(tempLL);
    getline(ss, tempLL,';');
    replaceChar(tempLL);
    temp.latitude=stod(tempLL);
    
    return temp;
}

//function to test parsed input
void printDEFIB(Defibrillator d){
    cout << "Defibrillator after parsing: " << endl;
    cout << "numID is: " << d.numID << endl;
    cout << "name is: " << d.name << endl;
    cout << "address is: " << d.address << endl;
    cout << "phone is: " << d.phone << endl;
    cout << "longitude is: " << d.longitude << endl;
    cout << "latitude is: " << d.latitude << endl;
}

int main(){
    
    string LON;
    cin >> LON; cin.ignore();
    replaceChar(LON,',','.');
    
    //DEBUG
    //cout << std::setprecision(15);
    
    string LAT;
    cin >> LAT; cin.ignore();
    replaceChar(LAT,',','.');
    
    int N;
    cin >> N; cin.ignore();
    
    double shortestDistance=numeric_limits<double>::max();
    Defibrillator answer; //will hold the answer
    
    for (int i = 0; i < N; i++) {
        string DEFIB;
        getline(cin, DEFIB);
        
        //DEBUG
        //cout << "Defibrillator before parsing: " << endl;
        //cout << DEFIB << endl;
        
        Defibrillator current = parseInput(DEFIB); //parse and store data of current defibrillator
        
        //DEBUG
        //printDEFIB(current);
        
        double currDistance = calcDistance(stod(LON),current.longitude,stod(LAT),current.latitude); //keep track of current distance
        
        //DEBUG
        //cout << "The distance to " << current.name << " is: " << currDistance << endl;
        
        if(currDistance<shortestDistance){
            answer=current;
            shortestDistance=currDistance;
        }
    }

    cout << answer.name << endl;
}