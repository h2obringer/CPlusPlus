//*******************************************************************
// File: amicableNumbers.cc
// 
// Author: Randy Obringer
// Email: ro120908@ohio.edu
//
// Problem:
//   let d(n) be defined as the sum of proper divisors of n (numbers 
//   less than n which divide evenly into n)
//   If d(a) = b and d(b) = a, where a != b, then a and b are an amicable pair 
//   and each of a and b are called amicable numbers.
//   For example, the proper divisors of 220 are 1,2,4,5,10,11,20,22,44,55,
//   and 110; therefore d(220)=284. The proper divisors of 284 are 1,2,4,71
//   and 142; so d(284)=220.
//
//   Evaluate the sum of all the amicable numbers under 10000.
//
// Answer: 31626
//
// Last Updated: 07/09/2011
//*******************************************************************

#include <iostream>
#include <string>
#include <set>
using namespace std;

int main(){
  int sum;
  int sum2;
  unsigned long long sumAmicables=0;
  set<int> amicable;
  for(int i=2;i<10001;i++){ //i<10001//build list of numbers and sum of their divisors below 10000
    sum=sum2=0;
    for(int j=1;j<i;j++){ // i = a, sum = b, sum2 = a, i = b.
      if(i%j==0){
        sum+=j;
      }
    }
    for(int k=1;k<sum;k++){
      if(sum%k==0){
        sum2+=k;
      }
    }
    if((i!=sum)&&(sum!=sum2)&&(i==sum2)){
      amicable.insert(sum);
      amicable.insert(i);
    }
  }
  set<int>::iterator it;
  for(it=amicable.begin();it!=amicable.end();++it){
    //cout << *it << endl;
    sumAmicables+=(*it);
  }
  cout << sumAmicables << endl;  
}
