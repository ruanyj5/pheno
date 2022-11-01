//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: fillmissing.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//

// Include Files
#include "fillmissing.h"
#include "NDVI46to365.h"
#include "interp1.h"
#include "phen_6method.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const double A[545]
//                double B[545]
// Return Type  : void
//
void fillmissing(const double A[545], double B[545])
{
  int i;
  boolean_T FAtmp[545];
  int ii;
  boolean_T exitg1;
  int ii_size_idx_0;
  short ii_data[545];
  int tmp_size[1];
  short tmp_data[545];
  int A_size[1];
  double b_tmp_data[545];
  int b_tmp_size[1];
  double A_data[545];
  double c_tmp_data[545];
  double d_tmp_data[545];
  int c_tmp_size[1];
  for (i = 0; i < 545; i++) {
    FAtmp[i] = rtIsNaN(A[i]);
    B[i] = A[i];
  }

  i = 0;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii < 545)) {
    if (!FAtmp[ii]) {
      i++;
      ii_data[i - 1] = static_cast<short>(ii + 1);
      if (i >= 545) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }

  if (1 > i) {
    ii_size_idx_0 = 0;
  } else {
    ii_size_idx_0 = i;
  }

  if (ii_size_idx_0 != 0) {
    int b_i;
    if (ii_size_idx_0 > 1) {
      int trueCount;
      trueCount = 0;
      ii = 0;
      for (i = 0; i < 545; i++) {
        if (FAtmp[i]) {
          trueCount++;
          tmp_data[ii] = static_cast<short>(i + 1);
          ii++;
        }
      }

      tmp_size[0] = ii_size_idx_0;
      for (b_i = 0; b_i < ii_size_idx_0; b_i++) {
        b_tmp_data[b_i] = (static_cast<double>(ii_data[b_i]) - 1.0) + 1.0;
      }

      A_size[0] = ii_size_idx_0;
      for (b_i = 0; b_i < ii_size_idx_0; b_i++) {
        A_data[b_i] = A[ii_data[b_i] - 1];
      }

      b_tmp_size[0] = trueCount;
      for (b_i = 0; b_i < trueCount; b_i++) {
        c_tmp_data[b_i] = (static_cast<double>(tmp_data[b_i]) - 1.0) + 1.0;
      }

      b_interp1(b_tmp_data, tmp_size, A_data, A_size, c_tmp_data, b_tmp_size,
                d_tmp_data, c_tmp_size);
      ii = 0;
      for (i = 0; i < 545; i++) {
        if (FAtmp[i]) {
          B[i] = d_tmp_data[ii];
          ii++;
        }
      }
    }

    b_i = ii_data[0] - 1;
    if (1 > b_i) {
      ii = 0;
    } else {
      ii = b_i;
    }

    for (i = 0; i < ii; i++) {
      B[i] = A[b_i];
    }

    if (ii_data[ii_size_idx_0 - 1] + 1 > 545) {
      b_i = 0;
      i = -1;
    } else {
      b_i = ii_data[ii_size_idx_0 - 1];
      i = 544;
    }

    ii = (i - b_i) + 1;
    for (i = 0; i < ii; i++) {
      B[b_i + i] = A[ii_data[ii_size_idx_0 - 1] - 1];
    }
  }
}

//
// File trailer for fillmissing.cpp
//
// [EOF]
//
