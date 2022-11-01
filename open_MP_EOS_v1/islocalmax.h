//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: islocalmax.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//
#ifndef ISLOCALMAX_H
#define ISLOCALMAX_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "NDVI46to365_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void b_islocalmax(const double A[364], boolean_T tf[364]);
extern void c_islocalmax(const double A[363], boolean_T tf[363]);
extern void d_islocalmax(const double A[362], boolean_T tf[362]);
extern void e_islocalmax(const double A[365], boolean_T tf[365]);
extern void islocalmax(const double A[365], boolean_T tf[365]);

#endif

//
// File trailer for islocalmax.h
//
// [EOF]
//
