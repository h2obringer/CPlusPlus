#ifndef LENGTH7_H
#define LENGTH7_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;

class length7{
  public:
    length7();
    long long hash(string &x,int M);
    void compute(); //brute force algorithm
    long long get0();
    long long get996();
    long long get500();
    long long get400();
    long long get211();
    long long getTotal();
  private:
    long long HASH0;
    long long HASH996;
    long long HASH500;
    long long HASH400;
    long long HASH211;
    long long TOTAL;
};

#endif
