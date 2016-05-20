#ifndef __BAND_LIB_NA_H__
#define __BAND_LIB_NA_H__

#include <typeinfo>

#include <stdint.h>
#include <string.h>

const int64_t R_NA_real = 0x7FF00000000007A2LL;

static inline void set_na(double *val)
{
  memcpy((void *) val, (void *) &R_NA_real, 8);
}

static inline void set_na(int *val)
{
  *val = INT32_MIN;
}


#endif
