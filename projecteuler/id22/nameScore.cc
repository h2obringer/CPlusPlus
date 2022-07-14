//******************************************************************
// File: nameScore.cc
//
// Author: Randy Obringer
// Email: ro120908@ohio.edu
//
// Problem: names.txt contains over 5000 first names. Sort the names
//   into alphabetical order and then work out the alphabetical value
//   of each name. Multiply this value by its alphabetical position in
//   the list to obtain its name score. Find the totoal of all the name
//   scores in the file.
//
// Answer: 871198282
//
// Last Updated: 07/04/2011
//******************************************************************

#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <string>
using namespace std;

int main(){
  list<string> mylist;
  char extra;
  ifstream ins;
  ins.open("names.txt");
  if(!ins.eof()){
    string name;
    while(ins){
      ins.get(extra); //quotation mark
      getline(ins,name,'"');
      ins.get(extra); //comma
      mylist.push_back(name);
    }
  }
  ins.close();
  mylist.sort();
  //test list
  list<string>::iterator it;
  int itemp;
  string stemp;
  int len;
  unsigned long long count=0;
  unsigned long long total=0;
  for(it=mylist.begin();it!=mylist.end();++it){
    count++;
    itemp=0;
    len=(*it).length();
    stemp=(*it);
    for(int i=0;i<len;i++){
      //cout << (stemp[i]-64) << " ";
      itemp+=(stemp[i]-64);
    }
    itemp=itemp*count;
    total+=itemp;
  }
  cout << "Total value of name scores: " << total << endl;
}
