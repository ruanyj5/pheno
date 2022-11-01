//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mean.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//

// Include Files
#include "mean.h"
#include "NDVI46to365.h"
#include "phen_6method.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const double x_data[]
//                const int x_size[2]
//                double y_data[]
//                int y_size[1]
// Return Type  : void
//
void mean(const double x_data[], const int x_size[2], double y_data[], int
          y_size[1])
{
  int vstride;
  int j;
  if (x_size[0] == 0) {
    y_size[0] = 0;
  } else {
    vstride = x_size[0];
    y_size[0] = static_cast<short>(x_size[0]);
    for (j = 0; j < vstride; j++) {
      y_data[j] = x_data[j] + x_data[vstride + j];
    }
  }

  vstride = y_size[0];
  for (j = 0; j < vstride; j++) {
    y_data[j] /= 2.0;
  }
}

//
// File trailer for mean.cpp
//
// [EOF]
//
