//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: phen_6method.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//
#ifndef PHEN_6METHOD_H
#define PHEN_6METHOD_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "NDVI46to365_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void phen_6method(double EXT09FEVI[545], const double EXT09DMSK2[545],
  const double ParamFit[4], double *Date1, double *Date2, double *Date3, double *
  Date4, double *Date5, double *Date6);

#endif

//
// File trailer for phen_6method.h
//
// [EOF]
//
