#include <iostream>

using namespace std;

int main() {
  
  int i;
  while (!cin.eof()) {
    cin >> i;
    if (!cin.fail())
      cout << i<< " times 4 = " << (i<<2) << endl;
  }
}
