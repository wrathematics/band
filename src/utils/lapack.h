#ifndef __BAND_LIB_LAPACK_H__
#define __BAND_LIB_LAPACK_H__


#include "types.h"

// FIXME all of these list c*_r, which can't be right...
// void dgbmv_(cchar_r trans, cint_r m, cint_r n, cint_r kl, cint_r ku, cdbl_r alpha, cdbl_r a, cint_r lda, cdbl_r x, cint_r incx, cdbl_r beta, cdbl_r y, cint_r incy);
// void dsbmv_(cchar_r uplo, cint_r n, cint_r k, cdbl_r alpha, cdbl_r a, cint_r lda, cdbl_r x, cint_r incx, cdbl_r beta, cdbl_r y, cint_r incy);
// void dtbmv_(cchar_r uplo, cchar_r trans, cchar_r diag, cint_r n, cint_r k, cdbl_r a, cint_r lda, cdbl_r x, cint_r incx);


// -----------------------------------------------------------------------------
// eigen problems
// -----------------------------------------------------------------------------

// divide and conquer method; slower than ?syevr
void dsyevd_(cchar_r, cchar_r, cint_r, double*, cint_r, double*, double*, int *,
  int*, int*, int*);
// relatively robust representations.
void dsyevr_(cchar_r, cchar_r, cchar_r, cint_r, double*, cint_r, cdbl_r, cdbl_r,
  cint_r, cint_r, cdbl_r, cint_r, double*, double*, cint_r, int*, double*, int*,
  int*, int*, int*);

// non-symmetric
void dgeev_(cchar_r, cchar_r, cint_r, double*, cint_r, double*, double*, double*,
  cint_r, double*, cint_r, double*, cint_r, int*);

// symmetric packed eigen
void dspev_(cchar_r, cchar_r, cint_r, cdbl_r, dbl_r, dbl_r, cint_r, dbl_r, int_r);


#endif
