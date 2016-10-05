#ifndef __BAND_LIB_TYPES_H__
#define __BAND_LIB_TYPES_H__

#include "../config.h"

#ifndef __cplusplus
#include <stdbool.h>
#endif

typedef const bool    cbool;
typedef const char    cchar;
typedef const int     cint;
typedef const double  cdbl;

typedef char *const restrict char_r;
typedef const char *const restrict cchar_r;

typedef int *const restrict int_r;
typedef const int *const restrict cint_r;

typedef double *const restrict dbl_r;
typedef const double *const restrict cdbl_r;


#endif
