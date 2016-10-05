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

#include "utils/cdefs.h"
#include "utils/indices.h"
#include "utils/safeomp.h"
#include "utils/types.h"


template <typename T>
static inline int symmetrize_full(cint triang, cint m, cint n, const T *const restrict x, T *const restrict s)
{
  if (triang == TRIANG_UPPER)
  {
    #pragma omp parallel for default(none) schedule(dynamic, 1) if(n*n>OMP_MIN_SIZE)
    for (int j=0; j<n; j+=BLOCKSIZE)
    {
      SAFE_SIMD
      for (int i=0; i<n; i+=BLOCKSIZE)
      {
        for (int col=j; col<j+BLOCKSIZE && col<n; ++col)
        {
          for (int row=i; row<i+BLOCKSIZE && row<n; ++row)
          {
            s[row + n*col] = x[row + m*col];
            s[col + n*row] = x[row + m*col];
          }
        }
      }
    }
  }
  else if (triang == TRIANG_LOWER)
  {
    #pragma omp parallel for default(none) schedule(dynamic, 1) if(n*n>OMP_MIN_SIZE)
    for (int j=0; j<n; j+=BLOCKSIZE)
    {
      SAFE_SIMD
      for (int i=0; i<n; i+=BLOCKSIZE)
      {
        for (int col=j; col<j+BLOCKSIZE && col<n; ++col)
        {
          for (int row=i; row<i+BLOCKSIZE && row<n; ++row)
          {
            s[col + n*row] = x[col + m*row];
            s[row + n*col] = x[col + m*row];
          }
        }
      }
    }
  }
  
  return 0;
}

extern "C" int symmetrize_full_int(cint triang, cint m, cint n, cint_r x, int_r s)
{
  return symmetrize_full(triang, m, n, x, s);
}

extern "C" int symmetrize_full_dbl(cint triang, cint m, cint n, cdbl_r x, dbl_r s)
{
  return symmetrize_full(triang, m, n, x, s);
}
