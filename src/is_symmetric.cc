/*  Copyright (c) 2016, Schmidt
    All rights reserved.
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    
    1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
    CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


// Storage reference: http://www.netlib.org/lapack/lug/node124.html
#include "band.h"
#include "indices.h"
#include "types.h"
#include <cfloat>
#include <cmath>


#define EPS 1000*FLT_EPSILON

static inline bool samenum(cint x, cint y)
{
  return (std::abs(x-y) == 0);
}

static inline bool samenum(cdbl x, cdbl y)
{
  return (std::abs(x-y) < EPS);
}



// interface
template <typename T>
bool is_symmetric(cint n, cint k, const T *band)
{
  const int nr = tobanded_numrows(k, k, false);
  const int len = nr*n;
  
  for (int j=0; j<n; j++)
  {
    const int nj = n*j;
    const int nrj = nr*j;
    const int imin = MAX(ind_imin(n, j, k, k), j+1);
    const int imax = ind_imax(n, j, k, k);
    
    for (int i=imin; i<=imax; i++)
    {
      const T t1 = band[ind_gen2band(nr, i, j, k)];
      const T t2 = band[ind_gen2band(nr, j, i, k)];
      
      if (!samenum(t1, t2))
        return false;
    }
  }
  
  return true;
}



// wrappers
extern "C" bool is_symmetric_int(cint n, cint k, const int *__restrict band)
{
  return is_symmetric(n, k, band);
}

extern "C" bool is_symmetric_dbl(cint n, cint k, const double *__restrict band)
{
  return is_symmetric(n, k, band);
}
