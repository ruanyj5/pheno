//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: NDVI46to365.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//

// Include Files
#include "NDVI46to365.h"
#include "NDVI46to365_data.h"
#include "NDVI46to365_initialize.h"
#include "fillmissing.h"
#include "interp1.h"
#include "islocalmax.h"
#include "phen_6method.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// MOD09DEVI=BlockDEVI(:,s); plot(BlockDEVI(:,s))  plot(MOD09DEVI)
//  MOD09DEVI(MOD09DEVI>1)=1;
//  MOD09DEVI(MOD09DEVI<0)=0;
// Arguments    : const double MOD09DEVI[46]
//                double EXT09Data[545]
//                double EXT09DMSK2[545]
//                double *LocMaxima
// Return Type  : void
//
void NDVI46to365(const double MOD09DEVI[46], double EXT09Data[545], double
                 EXT09DMSK2[545], double *LocMaxima)
{
  int i;
  double b_MOD09DEVI[365];
  double dv[365];
  double dv1[46];
  double d;
  boolean_T MaxLoctn[365];
  boolean_T ex;
  int idx;
  int k;
  boolean_T exitg1;
  double b_ex;
  double c_ex;
  short tmp_data[365];
  short b_tmp_data[365];
  int iindx;
  double b_EXT09Data[545];
  if (!isInitialized_NDVI46to365) {
    NDVI46to365_initialize();
  }

  //  46 to 365
  for (i = 0; i < 365; i++) {
    b_MOD09DEVI[i] = 0.0;
    dv[i] = static_cast<double>(i) + 1.0;
  }

  for (i = 0; i < 46; i++) {
    dv1[i] = 8.0 * static_cast<double>(i) + 4.5;
  }

  interp1Linear(MOD09DEVI, dv, b_MOD09DEVI, dv1);
  for (i = 0; i < 365; i++) {
    d = b_MOD09DEVI[i];
    if (b_MOD09DEVI[i] > 1.0) {
      d = 1.0;
      b_MOD09DEVI[i] = 1.0;
    }

    if (d < 0.0) {
      b_MOD09DEVI[i] = 0.0;
    }
  }

  //  detecting local maxima
  islocalmax(b_MOD09DEVI, MaxLoctn);

  //  3
  ex = rtIsNaN(b_MOD09DEVI[0]);
  if (!ex) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k <= 365)) {
      if (!rtIsNaN(b_MOD09DEVI[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    b_ex = b_MOD09DEVI[0];
  } else {
    b_ex = b_MOD09DEVI[idx - 1];
    i = idx + 1;
    for (k = i; k < 366; k++) {
      d = b_MOD09DEVI[k - 1];
      if (b_ex < d) {
        b_ex = d;
      }
    }
  }

  // max(MOD09DEVI,[],1)
  if (!ex) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k <= 365)) {
      if (!rtIsNaN(b_MOD09DEVI[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    c_ex = b_MOD09DEVI[0];
  } else {
    c_ex = b_MOD09DEVI[idx - 1];
    i = idx + 1;
    for (k = i; k < 366; k++) {
      d = b_MOD09DEVI[k - 1];
      if (c_ex > d) {
        c_ex = d;
      }
    }
  }

  //  local maximum EVI must be greater than 0.7 annual maximum EVI
  idx = 0;
  k = 0;
  for (i = 0; i < 365; i++) {
    ex = (b_MOD09DEVI[i] < 0.7 * b_ex);
    if (ex) {
      idx++;
      tmp_data[k] = static_cast<short>(i + 1);
      k++;
    }
  }

  for (i = 0; i < idx; i++) {
    MaxLoctn[tmp_data[i] - 1] = false;
  }

  //  local change range must be greater than 0.35 annual change range
  idx = 0;
  k = 0;
  for (i = 0; i < 365; i++) {
    ex = (b_MOD09DEVI[i] - c_ex < 0.35 * (b_ex - c_ex));
    if (ex) {
      idx++;
      b_tmp_data[k] = static_cast<short>(i + 1);
      k++;
    }
  }

  for (i = 0; i < idx; i++) {
    MaxLoctn[b_tmp_data[i] - 1] = false;
  }

  //  pad values for extended observations
  for (i = 0; i < 90; i++) {
    EXT09Data[i] = rtNaN;
  }

  std::memcpy(&EXT09Data[90], &b_MOD09DEVI[0], 365U * sizeof(double));
  for (i = 0; i < 90; i++) {
    EXT09Data[i + 455] = rtNaN;
  }

  //  obtain first local maxima
  iindx = 1;
  ex = MaxLoctn[0];
  for (k = 0; k < 364; k++) {
    if (static_cast<int>(ex) < static_cast<int>(MaxLoctn[k + 1])) {
      ex = true;
      iindx = k + 2;
    }
  }

  *LocMaxima = iindx;
  for (i = 0; i < 545; i++) {
    if (i - 89 > iindx) {
      EXT09Data[i] = rtNaN;
    }
  }

  //  obtain first local minima
  if (!rtIsNaN(EXT09Data[0])) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 546)) {
      if (!rtIsNaN(EXT09Data[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    idx = 1;
  } else {
    b_ex = EXT09Data[idx - 1];
    i = idx + 1;
    for (k = i; k < 546; k++) {
      d = EXT09Data[k - 1];
      if (b_ex > d) {
        b_ex = d;
        idx = k;
      }
    }
  }

  //  filling values
  //  tic
  //  toc
  //  mask values for extended observations
  //  EXT09DEVI(~EXT09DMSK)=nan;
  for (i = 0; i < 545; i++) {
    if (i - 89 < idx - 90) {
      EXT09Data[i] = rtNaN;
    }

    EXT09DMSK2[i] = ((i - 89 <= iindx + 90) && (i - 89 >= idx - 180));
  }

  std::memcpy(&b_EXT09Data[0], &EXT09Data[0], 545U * sizeof(double));
  fillmissing(b_EXT09Data, EXT09Data);
}

//
// File trailer for NDVI46to365.cpp
//
// [EOF]
//
