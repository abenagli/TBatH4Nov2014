#ifndef __complessi__
#define __complessi__

#include<cmath>
#include<iostream>



class complessi
{
 friend std::ostream& operator<< (std::ostream&, const complessi& z);
 friend std::istream& operator>> (std::istream&, complessi& z);
 
 public:
  
  //! default ctor
  complessi();
  //! ctor
  complessi(const float& a);
  complessi(const float& a, const float& b);
  //! copy ctor
  complessi(const complessi& z);
  
  //! dtor
  ~complessi();
  
  
  //! metodi
  float Re() const { return re_p; };
  float Imm() const { return imm_p; };
  
  float Mod() const { return mod_p; };
  float Arg() const { return arg_p; };
  
  complessi Coniugato() const;
  
  
  //! overloading
  complessi& operator=(const complessi& z);
  
  complessi operator+(const complessi& z) const;
  complessi& operator+();
  complessi& operator+=(const complessi& z);
  
  complessi operator-(const complessi& z) const;
  complessi& operator-();
  complessi& operator-=(const complessi& z);
  
  complessi operator*(const complessi& z) const;
  complessi& operator*=(const complessi& z);
  
  complessi operator/(const complessi& z) const;
  complessi& operator/=(const complessi& z);
  
  
  
 private:
  
  float re_p;
  float imm_p;
  float mod_p;
  float arg_p;
  
  void CalcolaMod();
  void CalcolaArg();
};

#endif
