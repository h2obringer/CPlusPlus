#include "nthPrime.h"

long long nthPrime::findNthPrime(int n,set<long long> &primes){
  int totalPrimes=2;
  long long current=4;
  set<long long>::iterator it;
  bool isPrime=true;
  while(totalPrimes<=n){
    for(it=primes.begin();it!=primes.end();++it){
      if(current%(*it)==0){
        isPrime=false;
        break;
      }
    }
    if(isPrime==true){
      primes.insert(current);
      totalPrimes++;
      if(totalPrimes==n){
        return current;
      }
    }
    isPrime=true;
    current++;
  }
}
