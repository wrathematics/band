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

#include <R.h>
#include <Rinternals.h>

#define INT(x) INTEGER(x)[0]
#define CHKRET(ret) if(ret) error("something went wrong")


SEXP R_tobanded(SEXP x, SEXP kl_, SEXP ku_)
{
  SEXP ret;
  const int kl = INT(kl_);
  const int ku = INT(ku_);
  const int m = nrows(x);
  const int n = ncols(x);
  const int m_out = tobanded_numrows(kl, ku, false);
  int check;
  
  switch (TYPEOF(x))
  {
    case INTSXP:
      PROTECT(ret = allocVector(INTSXP, m_out*n));
      check = tobanded_int(m, n, kl, ku, INTEGER(x), INTEGER(ret));
      break;
    case REALSXP:
      PROTECT(ret = allocVector(REALSXP, m_out*n));
      check = tobanded_dbl(m, n, kl, ku, REAL(x), REAL(ret));
      break;
    case LGLSXP:
      PROTECT(ret = allocVector(LGLSXP, m_out*n));
      check = tobanded_lgl(m, n, kl, ku, LOGICAL(x), LOGICAL(ret));
      break;
    default:
      error("bad type");
  }
  
  UNPROTECT(1);
  CHKRET(check);
  
  return ret;
}



#include <string.h>
SEXP R_tomatrix(SEXP x, SEXP m_, SEXP n_, SEXP kl_, SEXP ku_)
{
  SEXP ret;
  const int m = INT(m_);
  const int n = INT(n_);
  const int kl = INT(kl_);
  const int ku = INT(ku_);
  int check;
  
  switch (TYPEOF(x))
  {
    case INTSXP:
      PROTECT(ret = allocMatrix(INTSXP, m, n));
      check = tomatrix_int(m, n, kl, ku, INTEGER(ret), INTEGER(x));
      break;
    case REALSXP:
      PROTECT(ret = allocMatrix(REALSXP, m, n));
      check = tomatrix_dbl(m, n, kl, ku, REAL(ret), REAL(x));
      break;
    default:
      error("bad type");
  }
  
  UNPROTECT(1);
  CHKRET(check);
  
  return ret;
}



SEXP R_printer(SEXP x, SEXP m_, SEXP n_, SEXP kl_, SEXP ku_)
{
  const int m = INT(m_);
  const int n = INT(n_);
  const int kl = INT(kl_);
  const int ku = INT(ku_);
  int check;
  
  switch (TYPEOF(x))
  {
    case INTSXP:
      check = matprinter_int(m, n, kl, ku, INTEGER(x));
      break;
    case REALSXP:
      check = matprinter_dbl(m, n, kl, ku, REAL(x));
      break;
    default:
      error("bad type");
  }
  
  CHKRET(check);
  
  return R_NilValue;
}
