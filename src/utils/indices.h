#ifndef __BAND_LIB_INDICES_H__
#define __BAND_LIB_INDICES_H__


#include "cdefs.h"
#include "types.h"


#define TRIANGLESUM(n) (n*(n+1))/2


// -----------------------------------------
// symmetric
// -----------------------------------------

// i, j 1-based
static inline int ind_sym(cint n2, cint i, cint j)
{
  return i + ((n2-j)*(j-1))/2 - 1;
}

// -----------------------------------------
// banded
// -----------------------------------------

// min/max i values
static inline int ind_imin(cint m, cint j, cint kl, cint ku)
{
  return MAX(0, j-ku);
}

static inline int ind_imax(cint m, cint j, cint kl, cint ku)
{
  return MIN(m-1, j+kl);
}

// vector index of in the band storage of the (i,j) pair with i,j coming from regular storage
static inline int ind_gen2band(cint nr, cint i, cint j, cint ku)
{
  return (ku + i - j) + nr*j;
}

// static inline void ind_band2gen(cint m, cint n, cint nr, int *i, int *j, cint bi, cint bj)
// {
//   
// }


#endif
