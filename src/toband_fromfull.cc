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

#include "utils/NA.hh"

#include "utils/indices.h"
#include "utils/safeomp.h"


// ncols is always the same as the input
extern "C" int tobanded_numrows(cint kl, cint ku, cbool symmetric)
{
  if (symmetric)
    return kl + 1;
  else
    return kl + ku + 1;
}



template <typename T>
static inline int banded_diag(cint m, cint n, const T *const restrict gen, T *const restrict band)
{
  int ind_band = 0;
  
  for (int ind_gen=0; ind_gen<m*n; ind_gen+=m+1)
  {
    band[ind_band] = gen[ind_gen];
    ind_band++;
  }
  
  return 0;
}


template <typename T>
static inline int banded_gen(cint m, cint n, cint kl, cint ku, const T *const restrict gen, T *const restrict band)
{
  const int nr = tobanded_numrows(kl, ku, false);
  const int len = nr*n;
  
  initialize_na(band, len);
  
  for (int j=0; j<n; j++)
  {
    const int mj = m*j;
    const int imin = ind_imin(m, j, kl, ku);
    const int imax = ind_imax(m, j, kl, ku);
    
    SAFE_FOR_SIMD
    for (int i=imin; i<=imax; i++)
      band[ind_gen2band(nr, i, j, ku)] = gen[i + mj];
  }
  
return 0;
}



// interface
template <typename T>
int tobanded(cint m, cint n, cint kl, cint ku, const T *const restrict gen, T *const restrict band)
{
  if (kl < 0 || ku < 0)
    return BAND_BADKDIMS;
  else if (kl == 0 && ku == 0)
    return banded_diag(m, n, gen, band);
  else
    return banded_gen(m, n, kl, ku, gen, band);
}



// wrappers
extern "C" int tobanded_int(cint m, cint n, cint kl, cint ku, cint_r gen, int_r band)
{
  return tobanded(m, n, kl, ku, gen, band);
}

extern "C" int tobanded_dbl(cint m, cint n, cint kl, cint ku, cdbl_r gen, dbl_r band)
{
  return tobanded(m, n, kl, ku, gen, band);
}
