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


#include "band.h"
#include "indices.h"
#include "NA.hh"
#include "omputils.h"
#include "types.h"


template <typename T>
int xpose_full(const int m, const int n, const T *const __restrict x, T *const __restrict tx)
{
  #pragma omp parallel for default(none) schedule(dynamic, 1) if(m*n>OMP_MIN_SIZE)
  for (int j=0; j<n; j+=BLOCKSIZE)
  {
    SAFE_SIMD
    for (int i=0; i<m; i+=BLOCKSIZE)
    {
      for (int col=j; col<j+BLOCKSIZE && col<n; ++col)
      {
        for (int row=i; row<i+BLOCKSIZE && row<m; ++row)
          tx[col + n*row] = x[row + m*col];
      }
    }
  }
  
  return 0;
}

extern "C" int xpose_full_int(cint m, cint n, const int *__restrict x, int *const __restrict tx)
{
  return xpose_full(m, n, x, tx);
}

extern "C" int xpose_full_dbl(cint m, cint n, const double *__restrict x, double *const __restrict tx)
{
  return xpose_full(m, n, x, tx);
}




template <typename T>
int xpose_band(cint m, cint n, cint kl, cint ku, const T *__restrict band, T *__restrict trans)
{
  const int nr = tobanded_numrows(kl, ku, false);
  const int len = nr*n;
  
  initialize_na(trans, len);
  
  for (int j=0; j<n; j++)
  {
    const int imin = ind_imin(m, j, kl, ku);
    const int imax = ind_imax(m, j, kl, ku);
    
    for (int i=imin; i<=imax; i++)
    {
      const int ind1 = ind_gen2band(nr, i, j, ku);
      const int ind2 = ind_gen2band(nr, j, i, kl);
      
      trans[ind2] = band[ind1];
    }
  }
  
  return 0;
}

extern "C" int xpose_band_int(cint m, cint n, cint kl, cint ku, const int *__restrict band, int *__restrict trans)
{
  return xpose_band(m, n, kl, ku, band, trans);
}

extern "C" int xpose_band_dbl(cint m, cint n, cint kl, cint ku, const double *__restrict band, double *__restrict trans)
{
  return xpose_band(m, n, kl, ku, band, trans);
}
