#include "length7.h"

int main(){
  length7 E;
  E.compute();
  long long a=E.get0();
  long long b=E.get996();
  long long c=E.get500();
  long long d=E.get400();
  long long e=E.get211();
  long long t=E.getTotal();

  cout << "0: " << a << "/" << t << endl;
  cout << "996: " << b << "/" << t << endl;
  cout << "500: " << c << "/" << t << endl;
  cout << "400: " << d << "/" << t << endl;
  cout << "211: " << e << "/" << t << endl;
}
