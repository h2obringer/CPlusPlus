//does not work
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <set>
using namespace std;

int ascending(int x){
  stringstream ss;
  ss << x;
  multiset<char> digits;
  while(!ss.fail()){
    char c;
    ss >> c;
    digits.insert(c);
  }
  string temp="";
  multiset<char>::iterator it;
  for(it=digits.begin();it!=digits.end();++it){
    temp+=*it;
  }
  
  return atoi(temp.c_str());
  
}

int descending(int x){
  stringstream ss;
  ss << x;
  multiset<char> digits;
  while(!ss.fail()){
    char c;
    ss >> c;
    digits.insert(c);
  }
  string temp="";
  multiset<char>::iterator it;
  for(it=digits.begin();it!=digits.end();++it){
    temp+=*it;
  }
  int len=temp.length();
  int steps;
  if(len%2==1){
    steps=(len/2)+1;
  }else{
    steps=len/2;
  }
  for(int i=0;i<steps;i++){
    swap(temp[i],temp[steps-i]);
  }
  return atoi(temp.c_str());
}

int findcapewrecker(int x, set<int> &cycle){
  int a=ascending(x);
  int b=descending(x);
  cout << a << " " << b << endl;
  //if((a==0)||(b==0)){
    //return b;}
  if(cycle.count(a)>0){
    return -1;
  }
  cycle.insert(a);
  cycle.insert(b);
  
  int c=a-b;
  if(c<0){
    c*=-1;
  }
  return findcapewrecker(c,cycle);
}

int main(){
  set<int> cycle;
  int x;
  cin >> x;
  /*cycle.insert(x);
  set<int>:: iterator it;
  for(it=cycle.begin();it!=cycle.end();++it){
    cout << *it << endl;
  }*/
  cout << ascending(121) << endl;
  int a=findcapewrecker(x,cycle);
  cout << a << endl;
}
