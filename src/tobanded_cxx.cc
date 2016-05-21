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
#include "NA.hh"
#include "omputils.h"
#include "indices.h"


// ncols is always the same as the input
extern "C" int tobanded_numrows(cint kl, cint ku, cbool symmetric)
{
  int nrows;
  
  if (symmetric)
    nrows = kl + 1;
  else
    nrows = kl + ku + 1;
  
  return nrows;
}



template <typename T>
static inline int banded_diag(cint m, cint n, const T *__restrict gen, T *__restrict band)
{
  int ind_gen;
  int ind_band = 0;
  
  for (ind_gen=0; ind_gen<m*n; ind_gen+=m+1)
  {
    band[ind_band] = gen[ind_gen];
    ind_band++;
  }
  
  return 0;
}


#include <stdio.h>
template <typename T>
static inline int banded_gen(cint m, cint n, cint kl, cint ku, const T *__restrict gen, T *__restrict band)
{
  int i, j;
  int mj, nrj;
  int imin, imax;
  const int nr = tobanded_numrows(kl, ku, false);
  const int len = nr*n;
  
  initialize_na(band, len);
  
  for (j=0; j<n; j++)
  {
    mj = m*j;
    nrj = nr*j;
    imin = ind_imin(m, j, kl, ku);
    imax = ind_imax(m, j, kl, ku);
    
    SAFE_FOR_SIMD
    for (i=imin; i<=imax; i++)
      band[ind_gen2band(nr, i, j, ku)] = gen[i + mj];
  }
  
return 0;
}



// interface
template <typename T>
int tobanded(cint m, cint n, cint kl, cint ku, const T *gen, T *band)
{
  if (kl < 0 || ku < 0)
    return INVALID_KDIMS;
  else if (kl == 0 && ku == 0)
    return banded_diag(m, n, gen, band);
  else
    return banded_gen(m, n, kl, ku, gen, band);
}



// wrappers
extern "C" int tobanded_int(cint m, cint n, cint kl, cint ku, const int *__restrict gen, int *__restrict band)
{
  return tobanded(m, n, kl, ku, gen, band);
}

extern "C" int tobanded_dbl(cint m, cint n, cint kl, cint ku, const double *__restrict gen, double *__restrict band)
{
  return tobanded(m, n, kl, ku, gen, band);
}
