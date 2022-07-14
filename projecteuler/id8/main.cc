//******************************************************************
//
//  File: main.cc
//  
//  Author: RandyObringer
//  Email: ro120908@ohio.edu
//
//  Problem: Find the highest product of 5 consecutive digits in
//    the 1000-digit number below
//
//  Last Updated: 6/16/2011
//
//******************************************************************

#include "greatestProduct.h"

int main(){
  vector<string> thousandDigitNumber; //50x20
  greatestProduct gp;
  thousandDigitNumber.push_back("73167176531330624919225119674426574742355349194934"); //0
  thousandDigitNumber.push_back("96983520312774506326239578318016984801869478851843"); //1
  thousandDigitNumber.push_back("85861560789112949495459501737958331952853208805511"); //2
  thousandDigitNumber.push_back("12540698747158523863050715693290963295227443043557"); //3
  thousandDigitNumber.push_back("66896648950445244523161731856403098711121722383113"); //4
  thousandDigitNumber.push_back("62229893423380308135336276614282806444486645238749"); //5
  thousandDigitNumber.push_back("30358907296290491560440772390713810515859307960866"); //6
  thousandDigitNumber.push_back("70172427121883998797908792274921901699720888093776"); //7
  thousandDigitNumber.push_back("65727333001053367881220235421809751254540594752243"); //8
  thousandDigitNumber.push_back("52584907711670556013604839586446706324415722155397"); //9
  thousandDigitNumber.push_back("53697817977846174064955149290862569321978468622482"); //10
  thousandDigitNumber.push_back("83972241375657056057490261407972968652414535100474"); //11
  thousandDigitNumber.push_back("82166370484403199890008895243450658541227588666881"); //12
  thousandDigitNumber.push_back("16427171479924442928230863465674813919123162824586"); //13
  thousandDigitNumber.push_back("17866458359124566529476545682848912883142607690042"); //14
  thousandDigitNumber.push_back("24219022671055626321111109370544217506941658960408"); //15
  thousandDigitNumber.push_back("07198403850962455444362981230987879927244284909188"); //16
  thousandDigitNumber.push_back("84580156166097919133875499200524063689912560717606"); //17
  thousandDigitNumber.push_back("05886116467109405077541002256983155200055935729725"); //18
  thousandDigitNumber.push_back("71636269561882670428252483600823257530420752963450"); //19
  
  int max=gp.findGreatest(thousandDigitNumber);
  cout << max << endl;
}
