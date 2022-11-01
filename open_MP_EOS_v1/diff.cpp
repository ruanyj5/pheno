//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: diff.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//

// Include Files
#include "diff.h"
#include "NDVI46to365.h"
#include "phen_6method.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                double y_data[]
//                int y_size[1]
// Return Type  : void
//
void diff(const double x_data[], const int x_size[1], double y_data[], int
          y_size[1])
{
  int dimSize;
  dimSize = x_size[0];
  if (x_size[0] == 0) {
    y_size[0] = 0;
  } else {
    int ixLead;
    ixLead = x_size[0] - 1;
    if (ixLead >= 1) {
      ixLead = 1;
    }

    if (ixLead < 1) {
      y_size[0] = 0;
    } else {
      y_size[0] = static_cast<short>(x_size[0] - 1);
      if (static_cast<short>(x_size[0] - 1) != 0) {
        int iyLead;
        double work_data_idx_0;
        ixLead = 1;
        iyLead = 0;
        work_data_idx_0 = x_data[0];
        for (int m = 2; m <= dimSize; m++) {
          double tmp1;
          tmp1 = x_data[ixLead] - work_data_idx_0;
          work_data_idx_0 = x_data[ixLead];
          ixLead++;
          y_data[iyLead] = tmp1;
          iyLead++;
        }
      }
    }
  }
}

//
// File trailer for diff.cpp
//
// [EOF]
//
