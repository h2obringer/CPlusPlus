//******************************************************************
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Program: ReversePolish.cc
//
//  Description: This is the class implementation and usage of a 
//    reverse polish calculator.
//
//  Assumptions: The string used is always in reverse polish notation
//    and the only possible operators are +,-,*,/
//
//  Last updated: 3/29/11
//
//******************************************************************

#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <cstdlib>
using namespace std;

//class declaration
class ReversePolish{
  public:
    int compute(const string &rpstring);
    string infix(const string &rpstring);
  private:
    void computeAndPushBack(stack<string> &s,stack<int> &n);
    void reverseStack(stack<string> &in);
    void fill_stack(const string &rps,stack<string> &s);
    void concatenate(stack<string> &s,stack<string> &n);
};

//***********************************************************************
//  Function: compute (public)
//
//  Parameters: a constant string given in reverse polish notation format
//    (passed by reference)
//
//  Effects: makes a stream out of the passed in string, then uses the 
//    stream to fill a stack. Then uses reverseStack to put the stack in
//    the form it was originally given in. Finally it uses computeAndPushBack
//    to do all sub-calculations and puts the answer on the top of the stack
//
//***********************************************************************

int ReversePolish::compute(const string &rpstring){
  stack<string> use;  //needed
  stack<int> numbers;  //needed
  istringstream in(rpstring);  //needed
 
  fill_stack(rpstring,use);
  reverseStack(use); //edit

  while(!use.empty()){
    if((use.top()=="+")||(use.top()=="-")||(use.top()=="*")|(use.top()=="/")){
      computeAndPushBack(use,numbers);
    }else{
      string convert=use.top();
      use.pop();
      int num = atoi(convert.c_str());   //convert string to integer
      numbers.push(num);
    }
  }//end while

  return numbers.top(); //answer of whole string
}

//************************************************************************
//  Function: infix (public)
//
//  Parameters: a constant string given in reverse polish notation format
//
//  Effects: makes a stream out of the passed in string, then uses the 
//    stream to fill a stack. It then uses the reversed stack to concatenate and 
//    arrive at a new string that is the original reverse polish string
//    turned into a normal mathematical expression. This is the string
//    that is returned.
//
//*************************************************************************

string ReversePolish::infix(const string &rpstring){
  stack<string> use;  //needed
  stack<string> numbers;

  fill_stack(rpstring,use);
  reverseStack(use);
 
  while(!use.empty()){
    if((use.top()=="+")||(use.top()=="-")||(use.top()=="*")|(use.top()=="/")){
      concatenate(use,numbers);
    }else{
      numbers.push(use.top());
      use.pop();
    }
  }//end while
  return numbers.top();  
};

  //helping functions

    
//******************************************************************
//  Function: concatenate (private to the class)
//  
//  Parameters: 
//    1: a stack of strings holding only "+","-","*", or "/" (passed by reference)
//    2: a stack of strings that only holds numbers (passed by reference)
//
//  Effects: Changes the stack of numbers to hold the concatenation of the top 2
//    strings of numbers with the symbol stack
//
//  This function is used by the infix function
//******************************************************************

void ReversePolish::concatenate(stack<string> &s,stack<string> &n){
  string temp1=n.top();
  n.pop();
  string temp2=n.top();  
  n.pop();            
  string result;
  if(s.top()=="+"){
    s.pop();
    result="("+temp2+"+"+temp1+")";
    n.push(result);
  }else if(s.top()=="-"){
    s.pop();
    result="("+temp2+"-"+temp1+")";
    n.push(result);
  }else if(s.top()=="*"){
    s.pop();
    result="("+temp2+"*"+temp1+")";
    n.push(result);
  }else if(s.top()=="/"){
    s.pop();
    result="("+temp2+"/"+temp1+")";
    n.push(result);
  }
};

//******************************************************************
//  Function: computeAndPushBack (private to the class)
//
//  Parameters:
//    1: a stack of strings with only "+","-","/", or "*" (passed by reference)
//    2: a stack of integers (passed by reference)
//
//  Effects: Changes the number stack to have the top element hold the computation
//    of the operator (gotten from the string stack), with the already existing 
//    top two elements of the number stack
// 
//  This function is used by the compute function
//******************************************************************
void ReversePolish::computeAndPushBack(stack<string> &s,stack<int> &n){
  int temp1=n.top();
  n.pop();
  int temp2=n.top();  
  n.pop();            
  int result;
  if(s.top()=="+"){
    s.pop();
    result=temp2+temp1;
    n.push(result);
  }else if(s.top()=="-"){
    s.pop();
    result=temp2-temp1;
    n.push(result);
  }else if(s.top()=="*"){
    s.pop();
    result=temp2*temp1;
    n.push(result);
  }else if(s.top()=="/"){
    s.pop();
    result=temp2/temp1;
    n.push(result);
  }
}

//******************************************************************
//  Function: reverseStack (private to the class)
//
//  Parameters: a stack of strings (passed by reference)
//
//  Effects: reverses the order of the stack
// 
//  This function is used by the compute and infix functions
//******************************************************************
void ReversePolish::reverseStack(stack<string> &in){
  stack<string> temp;
  while(!in.empty()){ //transfer terms stack to use stack (upsidedown)
    temp.push(in.top());
    in.pop();
  }
  in=temp;
}

//******************************************************************
//  Function: fill_stack (private to the class)
//
//  Parameters: 
//    1: a constant string (passed by reference)
//    2: a stack of strings (passed by reference)
//
//  Effects: Changes the number stack to have the top element hold the computation
//    of the operator (gotten from the string stack), with the already existing 
//    top two elements of the number stack
// 
//  This function is used by the compute and infix functions
//******************************************************************
void ReversePolish::fill_stack(const string &rps,stack<string> &s){
  istringstream in(rps);  //needed
  while(!in.fail()){ //fill up the first stack
    string b;
    in >> b;    //new function?: void fill_stack(&istringstream ins,stack<string> &s
    if(b!=""){
      s.push(b);
    }
  }
}

int main(){
  ReversePolish obj;
  string a = "78 97 21 14 + + *";
  int numb=obj.compute(a);
  string exp=obj.infix(a);
  cout << numb << endl;
  cout << exp << endl;
}
