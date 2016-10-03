#ifndef __BAND_LIB_NA_H__
#define __BAND_LIB_NA_H__

#include "omputils.h"
#include <stdint.h>
#include <string.h>


static inline void initialize_na(double *x, const int len)
{
  static const int64_t R_NA_real = 0x7FF00000000007A2LL;
  
  SAFE_FOR_SIMD
  for (int i=0; i<len; i++)
    memcpy(x + i, &R_NA_real, sizeof(*x));
}

static inline void initialize_na(int *x, const int len)
{
  SAFE_FOR_SIMD
  for (int i=0; i<len; i++)
    x[i] = INT32_MIN;
}


#endif
