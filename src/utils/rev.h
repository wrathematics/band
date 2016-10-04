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

#ifndef __BAND_LIB_REV_H__
#define __BAND_LIB_REV_H__


#include <stdlib.h>
#include <string.h>

#include "safeomp.h"


static inline void reverse_vec(const int len, double *const x)
{
  int j = len-1;
  
  SAFE_FOR_SIMD
  for (int i=0; i<len/2; i++)
  {
    const double tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
    j--;
  }
}



// reverse columns of a column-major matrix
static inline void reverse_mat(const int m, const int n, double *const x)
{
  int last = n - 1;
  
  for (int j=0; j<n/2; j++)
  {
    #pragma omp parallel for if(m>1000)
    for (int i=0; i<m; i++)
    {
      const double tmp = x[i + m*j];
      x[i + m*j] = x[i + m*last];
      x[i + m*last] = tmp;
    }
    
    last--;
  }
}


#endif
