//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: NDVI46to365_initialize.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//

// Include Files
#include "NDVI46to365_initialize.h"
#include "NDVI46to365.h"
#include "NDVI46to365_data.h"
#include "phen_6method.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void NDVI46to365_initialize()
{
  rt_InitInfAndNaN();
  omp_init_nest_lock(&emlrtNestLockGlobal);
  isInitialized_NDVI46to365 = true;
}

//
// File trailer for NDVI46to365_initialize.cpp
//
// [EOF]
//
