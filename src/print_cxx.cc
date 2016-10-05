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


// If wanting to use outside of R, delete these headers and change macro to printf
#include <R.h>
#include <Rinternals.h>

#include "utils/types.h"

#define PRINTFUN Rprintf
// end of non-portable stuff


#define MAXROWS 10

#define MIN(a,b) (a<b?a:b)

template <typename T>
static T maxabsval(cint m, cint n, T* x)
{
  int mj;
  T tmp;
  T ret = 0;
  
  for (int j=0; j<n; j++)
  {
    mj = m*j;
    for (int i=0; i<m; i++)
    {
      tmp = x[i + mj];
      if (abs(tmp) > ret)
        ret = tmp;
    }
  }
  
  return ret;
}



template <typename T>
void matprinter(cint m, cint n, cint kl, cint ku, const char c, T *x)
{
  int toprow = MIN(MAXROWS, m);
  int spaces;
  
  for (int i=0; i<toprow; i++)
  {
    PRINTFUN("%d ", i+1);
    
    for (int j=0; j<n; j++)
    {
      
    }
  }
}



// wrappers
extern "C" void matprinter_int(cint m, cint n, cint kl, cint ku, cint *x)
{
  matprinter(m, n, kl, ku, 'd', x);
}

extern "C" void matprinter_dbl(cint m, cint n, cint kl, cint ku, cdbl *x)
{
  matprinter(m, n, kl, ku, 'f', x);
}
