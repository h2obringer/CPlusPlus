#include "nthPrime.h"

int main(){
  set<long long> primes;
  primes.insert(2);
  primes.insert(3);

  nthPrime np;
  long long i=np.findNthPrime(10001,primes);
  cout << i << endl;
}
