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
#include <string.h>

#include "band.h"

#include "lapack.h"
#include "safeomp.h"


static inline void reverse(const int len, double *x)
{
  int j = len-1;
  for (int i=0; i<len/2; i++)
  {
    const double tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
    j--;
  }
}

// work is at least length n
static inline void reverse_mat(const int n, double *x, double *work)
{
  int last = n-1;
  for (int j=0; j<n/2; j++)
  {
    memcpy(work, x + n*j, n*sizeof(*work));
    memcpy(x + n*j, x + n*last, n*sizeof(*work));
    memcpy(x + n*last, work, n*sizeof(*work));
    last--;
  }
}

static inline SEXP setret(SEXP values, SEXP vectors)
{
  SEXP ret, retnames;
  
  PROTECT(ret = allocVector(VECSXP, 2));
  PROTECT(retnames = allocVector(STRSXP, 2));
  
  SET_VECTOR_ELT(ret, 0, values);
  SET_VECTOR_ELT(ret, 1, vectors);
  SET_STRING_ELT(retnames, 0, mkChar("values"));
  SET_STRING_ELT(retnames, 1, mkChar("vectors"));
  setAttrib(ret, R_NamesSymbol, retnames);
  
  return ret;
}



// ----------------------------------------------------------------------------
// full storage
// ----------------------------------------------------------------------------

// divide 'n conquer method
static inline int eig_sym_dnc(const bool inplace, const bool only_values, const int n, double *restrict x, double *restrict values, double *restrict vectors)
{
  int info = 0;
  double *x_cp;
  // Passed to Fortran
  double worksize;
  int lwork, liwork;
  int *iwork;
  double *work;
  
  char jobz;
  
  if (only_values)
    jobz = 'N';
  else
    jobz = 'V';
  
  if (inplace)
    x_cp = x;
  else
  {
    memcpy(vectors, x, n*n*sizeof(double));
    x_cp = vectors;
  }
  
  
  dsyevd_(&jobz, &(char){'U'}, &n, x_cp, &n, values, &worksize, &(int){-1}, &liwork, &(int){-1}, &info);
  
  lwork = (int) worksize;
  work = malloc(lwork * sizeof(*work));
  iwork = malloc(liwork * sizeof(*iwork));
  
  dsyevd_(&jobz, &(char){'U'}, &n, x_cp, &n, values, work, &lwork, iwork, &liwork, &info);
  
  
  free(work);
  free(iwork);
  
  return info;
}



// relatively robust representations
static inline int eig_sym_rrr(const bool inplace, const bool only_values, const int n, double *restrict x, double *restrict values, double *restrict vectors)
{
  int info = 0;
  double *x_cp;
  // Passed to Fortran
  double worksize;
  int lwork, liwork;
  int *iwork;
  double *work;
  
  
  if (inplace)
    x_cp = x;
  else
  {
    memcpy(vectors, x, n*n*sizeof(double));
    x_cp = vectors;
  }
  
  
  char jobz;
  
  if (only_values)
    jobz = 'N';
  else
    jobz = 'V';
  
  // dsyevr_(&jobz, &(char){'A'}, &(char){'U'}, &n, x_cp, &n, 
  //   &(double){0.0}, &(double){0.0}, &(int){0}, &(int){0}, &(double){0.0}, 
  //   m, w, z, ldz, isuppz, &worksize, &(int){-1}, &liwork, &(int){-1}, &info);
  // lwork = (int) worksize;
  // work = malloc(lwork * sizeof(*work));
  // iwork = malloc(liwork * sizeof(*iwork));
  // dsyevr_(jobz, range, uplo, n, a, lda, vl, vu, il, iu, abstol, m, w, z, ldz, isuppz, work, &lwork, iwork, &liwork, &info);
  
  free(work);
  free(iwork);
  
  return info;
}



static inline int eig_nonsym(const bool inplace, const bool only_values, const int n, double *restrict x, double *restrict values, double *restrict vectors)
{
  int info = 0;
  
  error("not done yet");
  
  // char jobvl = 'n', jobvr;
  // 
  // if (only_values)
  //   jobvr = 'v';
  // else
  //   jobvr = 'n';
  // 
  // dgeev_(jobvl, jobvr, &n, x, &m, wr, wi, vl, ldvl, vr, ldvr, work, lwork, info);
  // dgeev_(jobvl, jobvr, n, a, lda, wr, wi, vl, ldvl, vr, ldvr, work, &neg1, info);
  
  return info;
}



static inline int eig(const bool inplace, const bool only_values, const bool symmetric, const int n, double *restrict x, double *restrict values, double *restrict vectors)
{
  if (symmetric)
    return eig_sym_dnc(inplace, only_values, n, x, values, vectors);
  else
    return eig_nonsym(inplace, only_values, n, x, values, vectors);
}



SEXP R_eig_full(SEXP x, SEXP symmetric_, SEXP onlyvals_, SEXP descending)
{
  SEXP ret, values, vectors;
  const int n = nrows(x);
  const int symmetric = INT(symmetric_);
  const int onlyvals = INT(onlyvals_);
  int ptct;
  double *values_ptr, *vectors_ptr;
  int info;
  
  if (n != ncols(x))
    error("argument 'x' is non-square");
  
  if (onlyvals)
  {
    vectors = R_NilValue;
    vectors_ptr = NULL;
    ptct = 3;
  }
  else
  {
    PROTECT(vectors = allocMatrix(REALSXP, n, n));
    vectors_ptr = REAL(vectors);
    ptct = 4;
  }
  
  PROTECT(values = allocVector(REALSXP, n));
  values_ptr = REAL(values);
  
  
  info = eig(false, onlyvals, symmetric, n, REAL(x), values_ptr, vectors_ptr);
  // if (info != 0)
  //   error("LAPACK function dspev() returned info=%d\n", info);
  
  if (INT(descending))
  {
    reverse(n, values_ptr);
    
    if (!onlyvals)
    {
      double *work = (double*) R_alloc(n, sizeof(*work));
      reverse_mat(n, vectors_ptr, work);
    }
  }
  
  ret = setret(values, vectors);
  
  UNPROTECT(ptct);
  return ret;

}



// ----------------------------------------------------------------------------
// symmetric matrix in packed storage
// ----------------------------------------------------------------------------
SEXP R_eig_sympacked(SEXP x, SEXP n_, SEXP triangle_, SEXP onlyvals_, SEXP descending)
{
  SEXP ret, values, vectors;
  const int n = INT(n_);
  const char triangle = CHARPT(triangle_, 0)[0];
  const int onlyvals = INT(onlyvals_);
  const int len = LENGTH(x);
  int ptct;
  char jobz;
  double *values_ptr, *vectors_ptr;
  double *x_cp, *work;
  int info;
  
  if (onlyvals)
  {
    vectors = R_NilValue;
    vectors_ptr = NULL;
    jobz = 'n';
    ptct = 3;
  }
  else
  {
    PROTECT(vectors = allocMatrix(REALSXP, n, n));
    vectors_ptr = REAL(vectors);
    jobz = 'v';
    ptct = 4;
  }
  
  PROTECT(values = allocVector(REALSXP, n));
  values_ptr = REAL(values);
  
  work = (double *) R_alloc(3*n, sizeof(*work));
  
  x_cp = (double *) R_alloc(len, sizeof(*x_cp));
  memcpy(x_cp, REAL(x), len*sizeof(*x_cp));
  
  dspev_(&jobz, &triangle, &n, x_cp, values_ptr, vectors_ptr, &n, work, &info);
  if (info != 0)
    error("LAPACK function dspev() returned info=%d\n", info);
  
  if (INT(descending))
  {
    reverse(n, values_ptr);
    if (!onlyvals)
      reverse_mat(n, vectors_ptr, work);
  }
  
  ret = setret(values, vectors);
  
  UNPROTECT(ptct);
  return ret;
}




// symmetric band: https://software.intel.com/en-us/node/469204#16C49C3C-0899-4467-BE98-60DACAD7D841
