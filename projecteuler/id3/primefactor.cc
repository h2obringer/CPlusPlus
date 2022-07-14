//what is the highest prime factor of a composite number? (number that is not prime

#include "primefactor.h"

long long primefactor::findHighestPrime(long long n,set<long long> &primes){
  bool isPrime=true;
  long long highest=1;
  set<long long>::iterator it;
  for(long long i=3;i<=n;i=i+2){
    for(it=primes.begin();it!=primes.end();++it){
      if(i%(*it)==0){
        isPrime=false;
        break;
      }
    }
    if(isPrime==true){
      primes.insert(i);
      if((n%i==0)&&(i>highest)){
        highest=i;
      }
    }
    isPrime=true;
  } 
  return highest;                
}

long long primefactor::highestFactor(long long n,set<long long> &primes){
  set<long long>::iterator it;
  long long highest=1;
  for(it=primes.begin();it!=primes.end();++it){
    if(((*it)>highest)&&(n%(*it)==0)){
      highest=(*it);
    }
  }
  return highest;
}
