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


#include <R.h>
#include <Rinternals.h>

#include "band.h"
#include "indices.h"

#define INT(x) INTEGER(x)[0]
#define CHARPT(x,i) ((char*)CHAR(STRING_ELT(x,i)))
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
    case REALSXP:
      PROTECT(ret = allocVector(REALSXP, m_out*n));
      check = tobanded_dbl(m, n, kl, ku, REAL(x), REAL(ret));
      break;
    case INTSXP:
      PROTECT(ret = allocVector(INTSXP, m_out*n));
      check = tobanded_int(m, n, kl, ku, INTEGER(x), INTEGER(ret));
      break;
    case LGLSXP:
      PROTECT(ret = allocVector(LGLSXP, m_out*n));
      check = tobanded_int(m, n, kl, ku, LOGICAL(x), LOGICAL(ret));
      break;
    default:
      error("bad type");
  }
  
  UNPROTECT(1);
  CHKRET(check);
  
  return ret;
}



SEXP R_tosymmetric(SEXP x, SEXP triangle_)
{
  SEXP ret;
  const int m = nrows(x);
  const int n = ncols(x);
  const int len = TRIANGLESUM(n);
  const char triangle = CHARPT(triangle_, 0)[0];
  int check;
  
  if (m != n)
    error("'x' must be a square matrix");
  
  switch (TYPEOF(x))
  {
    case REALSXP:
      PROTECT(ret = allocVector(REALSXP, len));
      check = tosymmetric_dbl(n, triangle, REAL(x), REAL(ret));
      break;
    case INTSXP:
      PROTECT(ret = allocVector(INTSXP, len));
      check = tosymmetric_int(n, triangle, INTEGER(x), INTEGER(ret));
      break;
    case LGLSXP:
      PROTECT(ret = allocVector(LGLSXP, len));
      check = tosymmetric_int(n, triangle, LOGICAL(x), LOGICAL(ret));
      break;
    default:
      error("bad type");
  }
  
  UNPROTECT(1);
  CHKRET(check);
  
  return ret;
}



SEXP R_tomatrix_fromband(SEXP x, SEXP m_, SEXP n_, SEXP kl_, SEXP ku_)
{
  SEXP ret;
  const int m = INT(m_);
  const int n = INT(n_);
  const int kl = INT(kl_);
  const int ku = INT(ku_);
  int check;
  
  switch (TYPEOF(x))
  {
    case REALSXP:
      PROTECT(ret = allocMatrix(REALSXP, m, n));
      check = tomatrix_fromband_dbl(m, n, kl, ku, REAL(ret), REAL(x));
      break;
    case INTSXP:
      PROTECT(ret = allocMatrix(INTSXP, m, n));
      check = tomatrix_fromband_int(m, n, kl, ku, INTEGER(ret), INTEGER(x));
      break;
    case LGLSXP:
      PROTECT(ret = allocMatrix(LGLSXP, m, n));
      check = tomatrix_fromband_int(m, n, kl, ku, LOGICAL(ret), LOGICAL(x));
      break;
    default:
      error("bad type");
  }
  
  UNPROTECT(1);
  CHKRET(check);
  
  return ret;
}



SEXP R_tomatrix_fromsym(SEXP x, SEXP n_, SEXP triangle_)
{
  SEXP ret;
  const int n = INT(n_);
  const char triangle = CHARPT(triangle_, 0)[0];
  int check;
  
  switch (TYPEOF(x))
  {
    case REALSXP:
      PROTECT(ret = allocMatrix(REALSXP, n, n));
      check = tomatrix_fromsym_dbl(n, triangle, REAL(ret), REAL(x));
      break;
    case INTSXP:
      PROTECT(ret = allocMatrix(INTSXP, n, n));
      check = tomatrix_fromsym_int(n, triangle, INTEGER(ret), INTEGER(x));
      break;
    case LGLSXP:
      PROTECT(ret = allocMatrix(LGLSXP, n, n));
      check = tomatrix_fromsym_int(n, triangle, LOGICAL(ret), LOGICAL(x));
      break;
    default:
      error("bad type");
  }
  
  UNPROTECT(1);
  CHKRET(check);
  
  return ret;
}



SEXP R_matprinter(SEXP x, SEXP m_, SEXP n_, SEXP kl_, SEXP ku_)
{
  const int m = INT(m_);
  const int n = INT(n_);
  const int kl = INT(kl_);
  const int ku = INT(ku_);
  
  switch (TYPEOF(x))
  {
    case REALSXP:
      matprinter_dbl(m, n, kl, ku, REAL(x));
      break;
    case INTSXP:
      matprinter_int(m, n, kl, ku, INTEGER(x));
      break;
    case LGLSXP:
      matprinter_int(m, n, kl, ku, LOGICAL(x));
      break;
    default:
      error("bad type");
  }
  
  return R_NilValue;
}



SEXP R_xposebanded(SEXP x, SEXP m_, SEXP n_, SEXP kl_, SEXP ku_)
{
  SEXP ret;
  const int m = INT(m_);
  const int n = INT(n_);
  const int kl = INT(kl_);
  const int ku = INT(ku_);
  int check;
  
  switch (TYPEOF(x))
  {
    case REALSXP:
      PROTECT(ret = allocMatrix(REALSXP, m, n));
      check = xposebanded_dbl(m, n, kl, ku, REAL(x), REAL(ret));
      break;
    case INTSXP:
      PROTECT(ret = allocMatrix(INTSXP, m, n));
      check = xposebanded_int(m, n, kl, ku, INTEGER(x), INTEGER(ret));
      break;
    case LGLSXP:
      PROTECT(ret = allocMatrix(LGLSXP, m, n));
      check = xposebanded_int(m, n, kl, ku, LOGICAL(x), LOGICAL(ret));
      break;
    default:
      error("bad type");
  }
  
  UNPROTECT(1);
  CHKRET(check);
  
  return ret;
}



SEXP R_is_symmetric(SEXP x, SEXP n_, SEXP k_)
{
  SEXP ret;
  const int n = INT(n_);
  const int k = INT(k_);
  int retval;
  
  switch (TYPEOF(x))
  {
    case REALSXP:
      retval = is_symmetric_dbl(n, k, REAL(x));
      break;
    case INTSXP:
      retval = is_symmetric_int(n, k, INTEGER(x));
      break;
    case LGLSXP:
      retval = is_symmetric_int(n, k, LOGICAL(x));
      break;
    default:
      error("bad type");
  }
  
  PROTECT(ret = allocVector(LGLSXP, 1));
  LOGICAL(ret)[0] = retval;
  UNPROTECT(1);
  
  return ret;
}
