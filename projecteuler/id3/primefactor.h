#ifndef PRIMEFACTOR_H
#define PRIMEFACTOR_H

#include <iostream>
#include <set>
using namespace std;

class primefactor{
  public:
    long long findHighestPrime(long long n,set<long long> &primes);
    long long highestFactor(long long n,set<long long> &primes); //don't need anymore

};

#endif
