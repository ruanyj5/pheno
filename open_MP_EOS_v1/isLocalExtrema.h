//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: isLocalExtrema.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//
#ifndef ISLOCALEXTREMA_H
#define ISLOCALEXTREMA_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "NDVI46to365_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void b_doLocalMaxSearch(double A[365], boolean_T maxVals[365], double P
  [365]);
extern void c_doLocalMaxSearch(double A_data[], const int A_size[1], boolean_T
  maxVals_data[], int maxVals_size[1], double P_data[], int P_size[1]);
extern void d_doLocalMaxSearch(double A[364], boolean_T maxVals[364], double P
  [364]);
extern void doLocalMaxSearch(double A_data[], const int A_size[1], const double
  x_data[], boolean_T maxVals_data[], int maxVals_size[1], double P_data[], int
  P_size[1]);
extern void e_doLocalMaxSearch(double A[363], boolean_T maxVals[363], double P
  [363]);
extern void f_doLocalMaxSearch(double A[362], boolean_T maxVals[362], double P
  [362]);
extern void g_doLocalMaxSearch(double A[365], boolean_T maxVals[365], double P
  [365]);

#endif

//
// File trailer for isLocalExtrema.h
//
// [EOF]
//
