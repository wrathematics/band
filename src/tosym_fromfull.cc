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


template <typename T>
static int symm_u(cint n, const T *const restrict full, T *const restrict sym)
{
  for (int j=0; j<n; j++)
  {
    int nj = n*j;
    SAFE_FOR_SIMD
    for (int i=0; i<=j; i++)
      sym[i + TRIANGLESUM(j)] = full[i + nj];
  }
  
  return 0;
}

#include <stdio.h>

template <typename T>
static int symm_l(cint n, const T *const restrict full, T *const restrict sym)
{
  const int n2 = n*2;
  
  for (int j=1; j<=n; j++)
  {
    int nj = n*(j-1);
    for (int i=j; i<=n; i++)
      sym[ind_sym(n2, i, j)] = full[(i-1) + nj];
  }
  
  return 0;
}

template <typename T>
int tosymmetric(cint n, cchar triangle, const T *const restrict full, T *const restrict sym)
{
  if (triangle == 'U' || triangle == 'u')
    return symm_u(n, full, sym);
  else if (triangle == 'L' || triangle == 'l')
    return symm_l(n, full, sym);
  else
    return -1;
}



// wrappers
extern "C" int tosymmetric_int(cint n, cchar triangle, cint_r full, int_r sym)
{
  return tosymmetric(n, triangle, full, sym);
}

extern "C" int tosymmetric_dbl(cint n, cchar triangle, cdbl_r full, dbl_r sym)
{
  return tosymmetric(n, triangle, full, sym);
}
