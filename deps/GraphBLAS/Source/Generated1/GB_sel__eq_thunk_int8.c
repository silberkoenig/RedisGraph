//------------------------------------------------------------------------------
// GB_sel:  hard-coded functions for selection operators
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2021, All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

//------------------------------------------------------------------------------

// If this file is in the Generated1/ folder, do not edit it
// (it is auto-generated from Generator/*).

#include "GB_select.h"
#include "GB_ek_slice.h"
#include "GB_sel__include.h"

// The selection is defined by the following types and operators:

// functions:
// phase1: GB (_sel_phase1__eq_thunk_int8)
// phase2: GB (_sel_phase2__eq_thunk_int8)
// bitmap: GB (_sel_bitmap__eq_thunk_int8)

// A type: int8_t

#define GB_ISO_SELECT \
    0

// kind
#define GB_ENTRY_SELECTOR

#define GB_ATYPE \
    int8_t

// test value of Ax [p]
#define GB_TEST_VALUE_OF_ENTRY(keep,p)                  \
    bool keep = (Ax [p] == thunk)

// Cx [pC] = Ax [pA], no typecast
#define GB_SELECT_ENTRY(Cx,pC,Ax,pA)                    \
    /* assignment skipped, C is iso with all entries equal to thunk */

//------------------------------------------------------------------------------
// GB_sel_phase1
//------------------------------------------------------------------------------



void GB (_sel_phase1__eq_thunk_int8)
(
    int64_t *restrict Zp,
    int64_t *restrict Cp,
    int64_t *restrict Wfirst,
    int64_t *restrict Wlast,
    const GrB_Matrix A,
    const bool flipij,
    const int64_t ithunk,
    const int8_t *restrict athunk,
    const GB_void *restrict ythunk,
    const GB_Operator op,
    const int64_t *A_ek_slicing, const int A_ntasks, const int A_nthreads
)
{ 
    int8_t thunk = (*athunk) ;
    
    #include "GB_select_phase1.c"
}



//------------------------------------------------------------------------------
// GB_sel_phase2
//------------------------------------------------------------------------------



void GB (_sel_phase2__eq_thunk_int8)
(
    int64_t *restrict Ci,
    int8_t *restrict Cx,
    const int64_t *restrict Zp,
    const int64_t *restrict Cp,
    const int64_t *restrict Cp_kfirst,
    const GrB_Matrix A,
    const bool flipij,
    const int64_t ithunk,
    const int8_t *restrict athunk,
    const GB_void *restrict ythunk,
    const GB_Operator op,
    const int64_t *A_ek_slicing, const int A_ntasks, const int A_nthreads
)
{ 
    int8_t thunk = (*athunk) ;
    
    #include "GB_select_phase2.c"
}



//------------------------------------------------------------------------------
// GB_sel_bitmap
//------------------------------------------------------------------------------



void GB (_sel_bitmap__eq_thunk_int8)
(
    int8_t *Cb,
    int8_t *restrict Cx,
    int64_t *cnvals_handle,
    GrB_Matrix A,
    const bool flipij,
    const int64_t ithunk,
    const int8_t *restrict athunk,
    const GB_void *restrict ythunk,
    const GB_Operator op,
    const int nthreads
)
{ 
    int8_t thunk = (*athunk) ;
    
    #include "GB_bitmap_select_template.c"
}


