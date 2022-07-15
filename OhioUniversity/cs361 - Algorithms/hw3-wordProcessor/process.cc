#include <iostream>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;
#include "WordNerd.cc"

string process(string in) {

  // Clean the string,
  // remove punctuation
  // make all uppercase to lower.

  string temp;
  for (int i=0;i<in.size();i++) {
    if (isalpha(in[i])) {
      temp+=tolower(in[i]);
    } else {
      temp+=' ';
    }
  }
  return temp;

}

int main() {
  ifstream instream; 
  ofstream outstream; 

  vector<string> output;

  instream.open("hobbit");
  outstream.open("hobbit.out");

//
//  while(!instream.eof())//
while (!cin.eof()) {
    string line,line1;

    getline(line);//getline(cin,line);
    if(!instream.fail()){//if (!cin.fail()) {
      line1=process(line);
      output.push_back(line1);
    }
  }

  for (int i=0;i<output.size();i++) {
    cout << i+1 << ":" << output[i] << endl;
    //outstream << i+1 << ":" << output[i] << endl;
  }
  instream.close();
  outstream.close();

  WordNerd obj;

  vector<string> t;
  t=obj.commonWords(output,4);

  cout << "Most Common words:" << endl;
  for (int j=0;j<t.size();j++) {
    cout << t[j] << endl;
  }
  t=obj.commonPalindromes(output,4);

  cout << "Most Common Palindromes:" << endl;
  for (int j=0;j<t.size();j++) {
    cout << t[j] << endl;
  }
  vector<list<string> > t1;
  t1 = obj.commonAnagrams(output,4);

  cout << "Most Common Anagrams:" << endl;
  for (int j=0;j<t1.size();j++) {
    for (list<string>::iterator p=t1[j].begin();p!=t1[j].end();++p) {
      if (p!=t1[j].begin()) { cout << ",";
      }
      cout << *p;
    }
    cout << endl;

  }
  


}

