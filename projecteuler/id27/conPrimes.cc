//Considering quadratics of the form:
//  n^2 + an + b, where |a| && |b| < 1000

//Find the product of the coefficients, a and b, for the quadratic expression that
// produces the maximum number of primes for consecutive values of n, starting with n=0.

//wrong answer: 17802032
#include <iostream>
#include <cstdlib>
#include <set>
using namespace std;

void findNthPrime(int n,set<long long> &primes){
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
      //if(totalPrimes==n){
      //  return current;
      //}
    }
    isPrime=true;
    current++;
  }
}

int main(){
  set<long long> primes;
  primes.insert(2);
  primes.insert(3);

  findNthPrime(200000,primes);
  set<long long>::iterator it;
  int maxInArow=0;
  int currentInArow=0; //n in quadratic formula
  long long current;
  bool contin=true;
  int a,b,product;
  for(int i=-1000;i<=1000;i++){
    for(int j=-1000;j<=1000;j++){
      while(contin==true){
        contin=false;
        current=(currentInArow*currentInArow)+(currentInArow*i)+j;
        for(it=primes.begin();it!=primes.end();++it){
          if(current==(*it)){
            currentInArow++;
            contin=true;
            break;
          }
        }
      }
      if(currentInArow>maxInArow){
        maxInArow=currentInArow;
        a=i;
        b=j;
      }
    }
  }
  product=a*b;
  cout << "Product: " << product << endl;
}
