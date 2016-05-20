#ifndef __BAND_LIB_NA_H__
#define __BAND_LIB_NA_H__

#include "omputils.h"
#include <stdint.h>

static const int64_t R_NA_real = 0x7FF00000000007A2LL;
static const int R_NA_int = INT32_MIN;

static inline void initialize_na(double *x, const int len)
{
  SAFE_FOR_SIMD
  for (int i=0; i<len; i++)
    x[i] = R_NA_real;
}

static inline void initialize_na(int *x, const int len)
{
  SAFE_FOR_SIMD
  for (int i=0; i<len; i++)
    x[i] = R_NA_int;
}


#endif
