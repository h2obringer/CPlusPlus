/*
Author: Randal Obringer
Date: ~2009
Description: Use bit shift operator to get all base 2 values
*/

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
