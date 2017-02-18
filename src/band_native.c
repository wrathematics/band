/* Automatically generated. Do not edit by hand. */

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h>

extern SEXP R_eig_full(SEXP x, SEXP onlyvals_, SEXP descending);
extern SEXP R_eig_sympacked(SEXP x, SEXP n_, SEXP triangle_, SEXP onlyvals_, SEXP descending);
extern SEXP R_isSym_band(SEXP x, SEXP n_, SEXP k_);
extern SEXP R_isSym_full(SEXP x);
extern SEXP R_matprinter(SEXP x, SEXP m_, SEXP n_, SEXP kl_, SEXP ku_);
extern SEXP R_symmetrize(SEXP x, SEXP triangle_);
extern SEXP R_tobanded(SEXP x, SEXP kl_, SEXP ku_);
extern SEXP R_tomatrix_fromband(SEXP x, SEXP m_, SEXP n_, SEXP kl_, SEXP ku_);
extern SEXP R_tomatrix_fromsym(SEXP x, SEXP n_, SEXP triangle_);
extern SEXP R_tosymmetric(SEXP x, SEXP triangle_);
extern SEXP R_xpose_band(SEXP x, SEXP m_, SEXP n_, SEXP kl_, SEXP ku_);
extern SEXP R_xpose_full(SEXP x);

static const R_CallMethodDef CallEntries[] = {
  {"R_eig_full", (DL_FUNC) &R_eig_full, 3},
  {"R_eig_sympacked", (DL_FUNC) &R_eig_sympacked, 5},
  {"R_isSym_band", (DL_FUNC) &R_isSym_band, 3},
  {"R_isSym_full", (DL_FUNC) &R_isSym_full, 1},
  {"R_matprinter", (DL_FUNC) &R_matprinter, 5},
  {"R_symmetrize", (DL_FUNC) &R_symmetrize, 2},
  {"R_tobanded", (DL_FUNC) &R_tobanded, 3},
  {"R_tomatrix_fromband", (DL_FUNC) &R_tomatrix_fromband, 5},
  {"R_tomatrix_fromsym", (DL_FUNC) &R_tomatrix_fromsym, 3},
  {"R_tosymmetric", (DL_FUNC) &R_tosymmetric, 2},
  {"R_xpose_band", (DL_FUNC) &R_xpose_band, 5},
  {"R_xpose_full", (DL_FUNC) &R_xpose_full, 1},
  {NULL, NULL, 0}
};
void R_init_band(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
