//******************************************************************
// File: sameBasePower.cc
// 
// Author: Randy Obringer
// Email: ro120908@ohio.edu
//
// Problem: Find the sum of 1^1+2^2+3^3+4^4+...+1000^1000
// 
// Answer: 333833500
//
// Last Updated: 07/10/2011
//*******************************************************************

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

string itos(int n){ //change int to string
  ostringstream out;
  out << n;
  return out.str();
}

int max(int a,int b){
  if(a>b){
    return a;
  }else{
    return b;
  }
}

int min(int a,int b){
  if(a<b){
    return a;
  }else{
    return b;
  }
}

int absolute_value(int a){
  if(a<0){
    a=-a;
  }
  return a;
}

int difference(int a,int b){
  int temp=a-b;
  return absolute_value(temp);
}

void format_strings(string &a,string &b){
  int length_a=a.length();
  int length_b=b.length();
  int diff=difference(length_a,length_b);
  if(length_a==length_b){
  }else if(length_a>length_b){
    for(int i=0;i<diff;i++){
      b="0"+b;
    }
  }else{
    for(int i=0;i<diff;i++){
      a="0"+a;
    }
  }
}

string add(int a,int b){
  string number1=itos(a);
  string number2=itos(b);
  format_strings(number1,number2);
  int _length=number1.length();
  int temp,digit,carry=0;
  string stemp,answer="";
  
  for(int i=_length-1;i>=0;i--){
    temp=(number1[i]-'0')+(number2[i]-'0')+carry;
    digit=temp%10;
    carry=temp/10;
    stemp=itos(digit);
    answer=stemp+answer;
  }
  
  if(carry==0){
    return answer;
  }else{
    stemp=itos(carry);
    answer=stemp+answer;
    return answer;
  }
}

string add(string number1,string number2){
  format_strings(number1,number2);
  int _length=number1.length();
  int temp,digit,carry=0;
  string stemp,answer="";
  
  for(int i=_length-1;i>=0;i--){
    temp=(number1[i]-'0')+(number2[i]-'0')+carry;
    digit=temp%10;
    carry=temp/10;
    stemp=itos(digit);
    answer=stemp+answer;
  }
  
  if(carry==0){
    return answer;
  }else{
    stemp=itos(carry);
    answer=stemp+answer;
    return answer;
  }
}

string multiply(int number1,int number2){
  //format_strings(a,b);
  string a=itos(number1);
  string b=itos(number2);
  int _length_a=a.length();
  int _length_b=b.length();
  int temp,digit,carry=0;
  string answer="0";
  string stemp,place_holder,temp_answer="";
  
  for(int i=_length_a-1;i>=0;i--){
    if(i!=_length_a-1){
      place_holder="0"+place_holder;
    }
    temp_answer="";
    for(int j=_length_b-1;j>=0;j--){
      temp=(a[i]-'0')*(b[j]-'0');
      temp+=carry;
      digit=temp%10;
      carry=temp/10;
      stemp=itos(digit);
      temp_answer=stemp+temp_answer;
    }
    if(carry!=0){
      stemp=itos(carry);
      temp_answer=stemp+temp_answer+place_holder;
    }else{
      temp_answer=temp_answer+place_holder;
    }
    answer=add(answer,temp_answer);
  }
  return answer;
}

string multiply(string a,string b){
  int _length_a=a.length();
  int _length_b=b.length();
  int temp,digit,carry=0;
  string answer="0";
  string stemp,place_holder,temp_answer="";
  
  for(int i=_length_a-1;i>=0;i--){
    if(i!=_length_a-1){
      place_holder="0"+place_holder;
    }
    temp_answer="";
    for(int j=_length_b-1;j>=0;j--){
      temp=(a[i]-'0')*(b[j]-'0');
      temp+=carry;
      digit=temp%10;
      carry=temp/10;
      stemp=itos(digit);
      temp_answer=stemp+temp_answer;
    }
    if(carry!=0){
      stemp=itos(carry);
      temp_answer=stemp+temp_answer+place_holder;
    }else{
      temp_answer=temp_answer+place_holder;
    }
    answer=add(answer,temp_answer);
  }
  return answer;
}

int main(){
  string total="0";
  string temp_total="1";
  string temp="";
  for(int i=1;i<=10;i++){
    temp_total="1";
    for(int j=1;j<=i;j++){
      temp=itos(i);
      temp_total=multiply(temp_total,temp);
    }
    total=add(temp_total,total);
  }
  cout << total << endl;
}
/*
string multiply(int a,int b){
  string number1=itos(a);
  string number2=itos(b);
  string place_holder="";
  string answer;
  
  for(int i=1;i<=number1.length();i++){
    for(int j=1;j<=number2.length();j++){
      
  

  return answer;
}

class BasePower{
  public:
    BasePower(int number1,int number2){ base=number1; power=number2; }
    calculate();
  private:
    string multiply(int a,int b);
    string add(int a,int b);
    const int power;
    int base;
}

BasePower::calculate(){
  string 
  string place_holder="";
  for(int i=1;i<=power;i++){
    multiply(base,i);
  }
    
}

BasePower BasePower::operator+(BasePower const& base_power){

}

int main(){
  string number="0"; //base 2
  string stempdigit,stempcarry,stemp,stempnumber,stempnumber2="";
  int itemp;
  int carry=0;
  int digit=0;
  int l1;
  int l2;
  int difference;
  for(int i=1;i<1001;i++){ //1001
    itemp=i*i;
    stempnumber=itos(itemp);
    l1=number.length();  		//format string for addition
    l2=stempnumber.length();		//
    digit=l2-l1;			//
    difference=abs(digit);		//
    if(l2>l1){				//
      for(int j=0;j<difference;j++){	//
        stempnumber2="0"+number;	//
        number=stempnumber2;		//
        //cout << "added 0" << endl;
      }					//
    }else if(l1>l2){			//
      for(int j=0;j<difference;j++){	//
        stempnumber2="0"+stempnumber;	//
        stempnumber=stempnumber2;	//
        //cout << "added 0" << endl;
      } 				//
    }		 			//format string for addition
    //number+stempnumber
    carry=0;
    stempnumber2=""; //reset
    stemp=number;
    for(int j=stemp.length()-1;j>=0;j--){
      itemp=(stemp[j]-'0')+(stempnumber[j]-'0')+carry;
      digit=itemp%10;
      carry=itemp/10;
      stempdigit=itos(digit);
      stempnumber2=stempdigit+stempnumber2;
      if((j==0)&&(carry>0)){
        stempcarry=itos(carry);
        stempnumber2=stempcarry+stempnumber2;
      }
    }
    number=stempnumber2;
    //cout << "i: " << i << " number: " << number << endl;
  }
  cout << number << endl;
}*/
