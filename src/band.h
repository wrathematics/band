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


#include "utils/cdefs.h"


#define INT(x) INTEGER(x)[0]
#define CHARPT(x,i) ((char*)CHAR(STRING_ELT(x,i)))
#define RCHECKRET(ret) if(ret) error("something went wrong")


#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

#include "utils/types.h"

// is_symmetric
bool isSym_full_int(cint n, cint_r x);
bool isSym_full_dbl(cint n, cdbl_r x);
bool isSym_band_int(cint n, cint k, cint_r band);
bool isSym_band_dbl(cint n, cint k, cdbl_r band);

// print
void matprinter_int(cint m, cint n, cint kl, cint ku, cint *x);
void matprinter_dbl(cint m, cint n, cint kl, cint ku, cdbl *x);

// symmetrize
int symmetrize_full_int(cint triang, cint m, cint n, cint_r x, int_r s);
int symmetrize_full_dbl(cint triang, cint m, cint n, cdbl_r x, dbl_r s);

// toband_fromfull
int tobanded_int(cint m, cint n, cint kl, cint ku, cint_r gen, int_r band);
int tobanded_dbl(cint m, cint n, cint kl, cint ku, cdbl_r gen, dbl_r band);

int tobanded_numrows(cint kl, cint ku, cbool symmetric);

// tomatrix_fromband
int tomatrix_fromband_int(cint m, cint n, cint kl, cint ku, int_r gen, cint_r band);
int tomatrix_fromband_dbl(cint m, cint n, cint kl, cint ku, dbl_r gen, cdbl_r band);

// tomatrix_fromsym
int tomatrix_fromsym_int(cint n, cchar triangle, int_r full, cint_r sym);
int tomatrix_fromsym_dbl(cint n, cchar triangle, dbl_r full, cdbl_r sym);

// tosym_fromfull
int tosymmetric_int(cint n, cchar tiangle, cint_r full, int_r sym);
int tosymmetric_dbl(cint n, cchar triangle, cdbl_r full, dbl_r sym);

// transpose
int xpose_full_int(cint m, cint n, cint_r x, int_r tx);
int xpose_full_dbl(cint m, cint n, cdbl_r x, dbl_r tx);
int xpose_band_int(cint m, cint n, cint kl, cint ku, cint_r band, int_r trans);
int xpose_band_dbl(cint m, cint n, cint kl, cint ku, cdbl_r band, dbl_r trans);


#ifdef __cplusplus
}
#endif


#endif
