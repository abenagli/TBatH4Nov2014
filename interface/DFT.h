#ifndef __DFT__
#define __DFT__

#include "complessi.h"

#include <vector>
#include <cmath>

#include "TF1.h"



// ---------------------------------------------------------
// Compute the DFT of N samples
// ---------------------------------------------------------

template <class T>
std::vector<complessi> DFT(const std::vector<T>& y)
{
  // define useful constants
  long double pi = 4.* atan(1.);
  complessi i(0, 1);
  
  
  // define the vector to save the DFT points
  std::vector<complessi> Y;
  
  
  // number of points to be discrete fourier transformed
  unsigned int N = y.size();
  
  
  // compute the DFT
  for(unsigned int it1 = 0; it1 < N; ++it1)
  {
    complessi temp;
    
    for(unsigned int it2 = 0; it2 < N; ++it2)
    {
      float coseno = cos(2.*pi/N*it1*it2);
      float seno = sin(2.*pi/N*it1*it2);
      
      temp += static_cast<complessi>(y.at(it2)) * ( static_cast<complessi>(coseno) - i * static_cast<complessi>(seno) );
    }
    
    Y.push_back(temp);
  }

  return Y;
}



// ---------------------------------------------------------
// Compute the IDFT of N samples
// ---------------------------------------------------------

template <class T>
std::vector<complessi> IDFT(const std::vector<T>& Y)
{
  // define useful constants
  long double pi = 4.* atan(1.);
  complessi i(0, 1);
  
  
  // define the vector to save the IDFT points
  std::vector<complessi> y;
  
  
  // number of points to be discrete fourier transformed
  unsigned int N = Y.size();
  
  
  // compute the IDFT
  for(unsigned int it1 = 0; it1 < N; ++it1)
  {
    complessi temp;
    
    for(unsigned int it2 = 0; it2 < N; ++it2)
    {
      float coseno = cos(2.*pi/N*it1*it2);
      float seno = sin(2.*pi/N*it1*it2);
      
      temp += static_cast<complessi>(Y.at(it2)) * ( static_cast<complessi>(coseno) + i * static_cast<complessi>(seno) );
    }
    
    y.push_back(temp/N);
  }
  
  return y;
}

#endif
