// 10/10
#include <iostream>
using namespace std;

int fibonacci(int x){
  int a=0;
  int b=1;
  int c=0;
  while(c<x){
    int temp1=a;
    int temp2=b;
    a=b;
    b=temp1+temp2;
    c+=1;
  }
  return a;
}

int tetra(int x){
  int a=0;
  int b=1;
  int c=1;
  int d=2;
  int i=0;
  while(i<x){
    int temp1=a;
    int temp2=b;
    int temp3=c;
    int temp4=d;
    a=b;
    b=c;
    c=d;
    d=temp1+temp2+temp3+temp4;
    i+=1;
  }
  return a;
}

void diffTF(int x){
  int a=tetra(x)-fibonacci(x);
  cout << a << endl;
}

int main(){
  int x;
  cin >> x;
  diffTF(x);
}
