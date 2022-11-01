//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: nullAssignment.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//

// Include Files
#include "nullAssignment.h"
#include "NDVI46to365.h"
#include "phen_6method.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : double x_data[]
//                int x_size[2]
//                const boolean_T idx_data[]
//                const int idx_size[1]
// Return Type  : void
//
void nullAssignment(double x_data[], int x_size[2], const boolean_T idx_data[],
                    const int idx_size[1])
{
  int nxin;
  int nxout;
  int k0;
  int k;
  nxin = x_size[1];
  nxout = 0;
  k0 = idx_size[0];
  for (k = 0; k < k0; k++) {
    nxout += idx_data[k];
  }

  nxout = x_size[1] - nxout;
  k0 = -1;
  for (k = 0; k < nxin; k++) {
    if ((k + 1 > idx_size[0]) || (!idx_data[k])) {
      k0++;
      x_data[k0] = x_data[k];
    }
  }

  if (1 > nxout) {
    x_size[1] = 0;
  } else {
    x_size[1] = nxout;
  }
}

//
// File trailer for nullAssignment.cpp
//
// [EOF]
//
