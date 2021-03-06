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


#include <string.h>

#include "band.h"

#include "utils/indices.h"
#include "utils/safeomp.h"


// Storage reference: http://www.netlib.org/lapack/lug/node124.html
template <typename T>
static inline int mat_diag(cint m, cint n, T *const restrict gen, const T *const restrict band)
{
  int ind_band = 0;
  
  memset(gen, 0, m*n*sizeof(T));
  
  for (int ind_gen=0; ind_gen<m*n; ind_gen+=m+1)
  {
    gen[ind_gen] = band[ind_band];
    ind_band++;
  }
  
  return 0;
}



template <typename T>
static inline int mat_gen(cint m, cint n, cint kl, cint ku, T *const restrict gen, const T *const restrict band)
{
  const int nr = tobanded_numrows(kl, ku, false);
  
  memset(gen, 0, m*n*sizeof(T));
  
  for (int j=0; j<n; j++)
  {
    const int mj = m*j;
    const int imin = ind_imin(m, j, kl, ku);
    const int imax = ind_imax(m, j, kl, ku);
    
    SAFE_FOR_SIMD
    for (int i=imin; i<=imax; i++)
      gen[i + mj] = band[ind_gen2band(nr, i, j, ku)];
  }
  
  return 0;
}



// interface
template <typename T>
int tomatrix_fromband(cint m, cint n, cint kl, cint ku, T *const restrict gen, const T *const restrict band)
{
  if (kl < 0 || ku < 0)
    return BAND_BADKDIMS;
  else if (kl == 0 && ku == 0)
    return mat_diag(m, n, gen, band);
  else
    return mat_gen(m, n, kl, ku, gen, band);
  
  return 0;
}



// wrappers
extern "C" int tomatrix_fromband_int(cint m, cint n, cint kl, cint ku, int_r gen, cint_r band)
{
  return tomatrix_fromband(m, n, kl, ku, gen, band);
}

extern "C" int tomatrix_fromband_dbl(cint m, cint n, cint kl, cint ku, dbl_r gen, cdbl_r band)
{
  return tomatrix_fromband(m, n, kl, ku, gen, band);
}
