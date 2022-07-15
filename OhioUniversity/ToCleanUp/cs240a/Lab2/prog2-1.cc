// 
// This C++ program can't be killed by Control-C.
//
// We'll use this to demonstrate the "kill" command
// in UNIX
//
#include <iostream>
#include <climits>
using namespace std;

extern "C" {
  #include <signal.h>
}

void new_control_c(int signal) {
  cout << "Control-C doesn't work on me!" << endl;
}

int main() {
  sigset(SIGINT,new_control_c);

  int new_val = (INT_MAX >> 5) + 17;

  while (new_val !=0) {
    cout << new_val << endl;
    new_val = new_val/2;
  }

}
