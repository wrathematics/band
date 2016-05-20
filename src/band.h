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

#ifndef __BAND_LIB_H__
#define __BAND_LIB_H__


#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

#define INVALID_KDIMS -1

#include "types.h"

// print
void matprinter_int(cint m, cint n, cint kl, cint ku, cint *x);
void matprinter_dbl(cint m, cint n, cint kl, cint ku, cdbl *x);

// tobanded
int tobanded_int(cint m, cint n, cint kl, cint ku, const int *__restrict gen, int *__restrict band);
int tobanded_dbl(cint m, cint n, cint kl, cint ku, const double *__restrict gen, double *__restrict band);

int tobanded_numrows(cint kl, cint ku, cbool symmetric);

// tomatrix
int tomatrix_int(cint m, cint n, cint kl, cint ku, int *__restrict gen, const int *__restrict band);
int tomatrix_dbl(cint m, cint n, cint kl, cint ku, double *__restrict gen, const double *__restrict band);

// transpose
int xposebanded_int(cint m, cint n, cint kl, cint ku, const int *__restrict band, int *__restrict trans);
int xposebanded_dbl(cint m, cint n, cint kl, cint ku, const double *__restrict band, double *__restrict trans);


#ifdef __cplusplus
}
#endif


#endif
