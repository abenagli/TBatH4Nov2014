#include "complessi.h"



//! friend operator --------------------------------------------------------------------------------

std::ostream& operator<< (std::ostream& os, const complessi& z)
{
  os << " (" << z.re_p << "," << z.imm_p << ") ";
  return os;
}



std::istream& operator>> (std::istream& is, complessi& z)
{
  float a,b;
  is >> a >> b;
  z = complessi (a,b);
  return is;
}






//! default ctor -----------------------------------------------------------------------------------

complessi::complessi():
 re_p (0),
 imm_p (0),
 mod_p (0),
 arg_p (0)
{}



//! ctor -------------------------------------------------------------------------------------------

complessi::complessi(const float& a):
 re_p (a),
 imm_p (0),
 mod_p (re_p),
 arg_p (0.)
{}



complessi::complessi(const float& a, const float& b):
 re_p (a),
 imm_p (b)
{
  CalcolaMod();
  CalcolaArg();
}



//! copy ctor ---------------------------------------------------------------------------------------

complessi::complessi(const complessi& z):
 re_p (z.re_p),
 imm_p (z.imm_p)
{
  CalcolaMod();
  CalcolaArg();
}



//! dtor -------------------------------------------------------------------------------------------

complessi::~complessi ()
{}






//! Calcola modulo/fase ----------------------------------------------------------------------------

void complessi::CalcolaMod()
{
  mod_p = sqrt(re_p*re_p + imm_p*imm_p);
}



void complessi::CalcolaArg()
{
  if(re_p != 0)
    arg_p = atan( imm_p/re_p );
  
  else
  {
    if(imm_p > 0)
      arg_p =  2. * atan(1.);
    else
      arg_p = -2. * atan(1.);
  }
}






complessi complessi::Coniugato() const
{
  complessi temp(re_p,
                 -imm_p);
  return temp;
}





//! overloading ------------------------------------------------------------------------------------

complessi& complessi::operator=(const complessi& z)
{
  re_p = z.re_p;
  imm_p = z.imm_p;
  
  CalcolaMod();
  CalcolaArg();
  
  return *this;
}



complessi complessi::operator+(const complessi& z) const
{
  complessi temp(re_p+z.re_p,
                 imm_p+z.imm_p);
  return temp;
}

complessi& complessi::operator+=(const complessi& z)
{
  re_p  += z.re_p;
  imm_p += z.imm_p;
  
  CalcolaMod();
  CalcolaArg();
  
  return *this;
}



complessi complessi::operator-(const complessi& z) const
{
  complessi temp(re_p-z.re_p,
                 imm_p-z.imm_p);
  return temp;
}

complessi& complessi::operator-()
{
  re_p  *= -1.;
  imm_p *= -1.;
  
  CalcolaMod();
  CalcolaArg();
  
  return *this;
}

complessi& complessi::operator-=(const complessi& z)
{
  re_p  -= z.re_p;
  imm_p -= z.imm_p;
  
  CalcolaMod();
  CalcolaArg();
  
  return *this;
}



complessi complessi::operator*(const complessi& z) const
{
  complessi temp(re_p*z.re_p - imm_p*z.imm_p,
                 re_p*z.imm_p + imm_p*z.re_p);
  return temp;
}

complessi& complessi::operator*=(const complessi& z)
{
  re_p =  re_p*z.re_p  - imm_p*z.imm_p;
  imm_p = re_p*z.imm_p + imm_p*z.re_p;
  
  CalcolaMod();
  CalcolaArg();
  
  return *this;
}



complessi complessi::operator/(const complessi& z) const
{
  double oneOverDen = 1. / (z.re_p*z.re_p + z.imm_p*z.imm_p);
  
  complessi temp( oneOverDen * (re_p  * z.re_p + imm_p * z.imm_p),
                  oneOverDen * (imm_p * z.re_p -  re_p * z.imm_p) );

  return temp;
}
