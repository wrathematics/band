#include <R.h>
#include <Rinternals.h>

#include "banded.h"

#define INT(x) INTEGER(x)[0]


SEXP R_banded(SEXP x, SEXP kl_, SEXP ku_)
{
  SEXP ret;
  const int kl = INT(kl_);
  const int ku = INT(ku_);
  const int m = nrows(x);
  const int n = ncols(x);
  const int m_out = banded_nr(kl, ku, false);
  
  switch (TYPEOF(x))
  {
    case INTSXP:
      PROTECT(ret = allocVector(INTSXP, m_out*n));
      banded_int(m, n, kl, ku, INTEGER(x), INTEGER(ret));
      break;
    case REALSXP:
      PROTECT(ret = allocVector(REALSXP, m_out*n));
      banded_double(m, n, kl, ku, REAL(x), REAL(ret));
      break;
    default:
      error("bad type");
  }
  
  UNPROTECT(1);
  return ret;
}
