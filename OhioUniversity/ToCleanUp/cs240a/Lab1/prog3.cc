// This program uses a variable called "new"....
// I don't quite know why it doesn't compile.....
//
//
//
#include <iostream>

using namespace std;
int main() {
  int new_var;


  new_var =INT_MAX;

  while (new_var !=0) {
    cout << new_var << endl;
    new_var = new_var >> 1;
  }


  new_var = INT_MIN;

  while (new_var !=-1) {
    cout << new_var << endl;
    new_var = new_var >> 1;
  }


  int delete_var;
  delete_var = 15;
  while (delete_var !=0) {
    cout << delete_var << endl;
    delete_var--;
  }



}
