#include <iostream>
#include "primefactor.h"
using namespace std;

int main(){
  primefactor P;
  set<long long> primes;
  primes.insert(2);
  primes.insert(3);
  long long number=P.findHighestPrime(600851475143,primes);
  //long long number=P.highestFactor(600851475143,primes);
  cout << number << endl;
}
