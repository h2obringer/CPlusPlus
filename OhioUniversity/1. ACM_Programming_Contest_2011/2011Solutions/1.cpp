// 5/10
#include <iostream>
using namespace std;

long long doublefactorial(long long x){
  if(x==-1){
    return 1;
  }else if(x==0){
    return 1;
  }else{
    return x*doublefactorial(x-2);
  }
}

long long factorial(long long x){
  if(x==0){
    return 1;
  }else{
    return x*factorial(x-1);
  }
}

void doubledoublefactorial(long long x){
  long long a=(factorial(x)-(2*doublefactorial(x)));
  cout << a << endl;
}

int main(){
  long long x;
  cin >> x;
  doubledoublefactorial(x);
}

/*int main(){
  long x=2*doublefactorial(15);
  cout << x << endl;
}*/
