#ifndef NTHPRIME_H
#define NTHPRIME_H

#include <iostream>
#include <set>
using namespace std;

class nthPrime{
  public:
    long long findNthPrime(int n,set<long long> &primes);
};

#endif
