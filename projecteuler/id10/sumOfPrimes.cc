//******************************************************************
//  File: sumOfPrimes.cc
//
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Problem: Find the sum of all the primes below 2-million
//
//  Last Updated: 6/16/2011
//  
//  Comment: Takes 5 minutes to solve answer
//  Answer: 142913828922
//******************************************************************

#include <iostream>
#include <set>
using namespace std;

int main(){
  set<long long> primes;
  set<long long>::iterator it;
  long long sum=2;
  bool isPrime=true;
  primes.insert(2);
  for(long long i=3;i<2000001;i++){
    for(it=primes.begin();it!=primes.end();++it){
      if(i%(*it)==0){
        isPrime=false;
        break;
      }
    }
    if(isPrime==true){
      primes.insert(i);
      sum+=i;
    }
    isPrime=true;
  }
  cout << sum << endl;  
}
