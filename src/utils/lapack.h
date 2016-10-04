#ifndef __BAND_LIB_LAPACK_H__
#define __BAND_LIB_LAPACK_H__


#include "types.h"

// FIXME all of these list c*_r, which can't be right...
// void dgbmv_(cchar_r trans, cint_r m, cint_r n, cint_r kl, cint_r ku, cdbl_r alpha, cdbl_r a, cint_r lda, cdbl_r x, cint_r incx, cdbl_r beta, cdbl_r y, cint_r incy);
// void dsbmv_(cchar_r uplo, cint_r n, cint_r k, cdbl_r alpha, cdbl_r a, cint_r lda, cdbl_r x, cint_r incx, cdbl_r beta, cdbl_r y, cint_r incy);
// void dtbmv_(cchar_r uplo, cchar_r trans, cchar_r diag, cint_r n, cint_r k, cdbl_r a, cint_r lda, cdbl_r x, cint_r incx);


// divide and conquer method; slower than ?syevr
void dsyevd_(cchar_r jobz, cchar_r uplo, cint_r n, double* a, cint_r lda, double* w, double *work, int *lwork, int *iwork, int *liwork, int *info);
// relatively robust representations.
void dsyevr_(cchar_r jobz, cchar_r range, cchar_r uplo, cint_r n, double *a, 
  cint_r lda, cdbl_r vl, cdbl_r vu, cint_r il, cint_r iu, cdbl_r abstol, 
  cint_r m, double *w, double *z, cint_r ldz, int *isuppz, double *work, 
  int *lwork, int *iwork, int *liwork, int *info);

// symmetric packed eigen
void dspev_(cchar_r jobz, cchar_r uplo, cint_r n, cdbl_r ap, dbl_r w, dbl_r z, cint_r ldz, dbl_r work, int_r info);


#endif
