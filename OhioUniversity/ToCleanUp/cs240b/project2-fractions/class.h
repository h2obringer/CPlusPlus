#ifndef CLASS_H
#define CLASS_H

//class definition
class fraction{
public:
  fraction();
  void input();
  fraction output();
  //void simplist_terms(int a,int b);
  // 
  // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  // ||||||||||||||||||||||||||||||||  
  //attempt at getting fractions to lowest
  //terms it does not work and I have tried a million different ways :(
  fraction operator+(fraction const& fract);
  fraction operator-(fraction const& fract);
  fraction operator*(fraction const& fract);
  fraction operator/(fraction const& fract);

  friend ostream &operator<<(ostream &outs, const fraction &frac);
  friend istream &operator>>(istream &ins, fraction &frac);
  
  int a,b;
  char divider;
};

#endif
