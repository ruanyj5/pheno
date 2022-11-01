//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: NDVI46to365.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//
#ifndef NDVI46TO365_H
#define NDVI46TO365_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "NDVI46to365_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void NDVI46to365(const double MOD09DEVI[46], double EXT09Data[545],
  double EXT09DMSK2[545], double *LocMaxima);

#endif

//
// File trailer for NDVI46to365.h
//
// [EOF]
//
