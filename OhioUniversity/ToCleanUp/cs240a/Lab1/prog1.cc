#include <iostream>

using namespace std;

int main() {
  
  unsigned int i,j;
  i = 1;
  j = 0;
  while (i!=0) {
    cout << "2^"<<j<<"=" << i << endl;
    i=i<<1;
    j++;
  }
}
