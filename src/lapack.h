#ifndef __BAND_LIB_LAPACK_H__
#define __BAND_LIB_LAPACK_H__


#include "type.h"

void dgbmv_(cchar_r trans, cint_r m, cint_r n, cint_r kl, cint_r ku, cdbl_r alpha, cdbl_r a, cint_r lda, cdbl_r x, cint_r incx, cdbl_r beta, cdbl_r y, cint_r incy);
void dsbmv_(cchar_r uplo, cint_r n, cint_r k, cdbl_r alpha, cdbl_r a, cint_r lda, cdbl_r x, cint_r incx, cdbl_r beta, cdbl_r y, cint_r incy);
void dtbmv_(cchar_r uplo, cchar_r trans, cchar_r diag, cint_r n, cint_r k, cdbl_r a, cint_r lda, cdbl_r x, cint_r incx);


#endif
