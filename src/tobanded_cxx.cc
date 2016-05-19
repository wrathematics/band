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
template <typename T>
static inline int banded_diag(const int m, const int n, const T *__restrict in, T *__restrict out)
{
  int ind_in;
  int ind_out = 0;
  
  for (ind_in=0; ind_in<m*n; ind_in+=m+1)
  {
    out[ind_out] = in[ind_in];
    ind_out++;
  }
  
  return 0;
}

template <typename T>
static inline int banded_gen(const int m, const int n, const int kl, const int ku, const T *__restrict in, T *__restrict out)
{
  int i, j;
  int mj;
  int ind = 0;
  

  
  return 0;
}

template <typename T>
int tobanded(const int m, const int n, const int kl, const int ku, const T *in, T *out)
{
  if (kl == 0 && ku == 0)
    return banded_diag(m, n, in, out);
  else
    return banded_gen(m, n, kl, ku, in, out);
}

extern "C" int tobanded_int(const int m, const int n, const int kl, const int ku, const int *__restrict in, int *__restrict out)
{
  return tobanded(m, n, kl, ku, in, out);
}

extern "C" int tobanded_double(const int m, const int n, const int kl, const int ku, const double *__restrict in, double *__restrict out)
{
  return tobanded(m, n, kl, ku, in, out);
}

// ncols is always the same as the input
extern "C" int tobanded_numrows(const int kl, const int ku, const bool symmetric)
{
  int nrows;
  
  if (symmetric)
    nrows = kl + 1;
  else
    nrows = kl + ku + 1;
  
  return nrows;
}
