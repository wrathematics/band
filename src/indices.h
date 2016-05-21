#ifndef __BAND_LIB_INDICES_H__
#define __BAND_LIB_INDICES_H__


#include "types.h"

#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)

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
