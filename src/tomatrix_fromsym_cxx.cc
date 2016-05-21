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
#include "omputils.h"
#include "indices.h"


template <typename T>
static int symm_u(cint n, T *__restrict full, const T *__restrict sym)
{
  const int len = TRIANGLESUM(n);
  
  for (int j=0; j<n; j++)
  {
    int nj = n*j;
    
    for (int i=0; i<=j; i++)
    {
      int ind = i + TRIANGLESUM(j);
      full[i + nj] = sym[ind];
      full[j + n*i] = sym[ind];
    }
    
    full[j + nj] = sym[j + TRIANGLESUM(j)];
  }
  
  return 0;
}

template <typename T>
static int symm_l(cint n, T *__restrict full, const T *__restrict sym)
{
  const int nn = n*n;
  const int len = TRIANGLESUM(n);
  
  for (int j=0; j<n; j++)
  {
    int nj = n*j;
    
    full[j + nj] = sym[j + ((nn-j)*(j-1))/2];
    
    for (int i=j+1; i<n; i++)
    {
      int ind = i + ((nn-j)*(j-1))/2;
      full[i + nj] = sym[ind];
      full[j + n*i] = sym[ind];
    }
  }
  
  return 0;
}

template <typename T>
int tomatrix_fromsym(cint n, cchar triangle, T *__restrict full, const T *__restrict sym)
{
  if (triangle == 'U' || triangle == 'u')
    return symm_u(n, full, sym);
  else if (triangle == 'L' || triangle == 'l')
    return symm_l(n, full, sym);
  else
    return -1;
}



// wrappers
extern "C" int tomatrix_fromsym_int(cint n, cchar triangle, int *__restrict full, const int *__restrict sym)
{
  return tomatrix_fromsym(n, triangle, full, sym);
}

extern "C" int tomatrix_fromsym_dbl(cint n, cchar triangle, double *__restrict full, const double *__restrict sym)
{
  return tomatrix_fromsym(n, triangle, full, sym);
}
