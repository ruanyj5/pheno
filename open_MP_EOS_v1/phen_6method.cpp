//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: phen_6method.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//

// Include Files
#include "phen_6method.h"
#include "NDVI46to365.h"
#include "NDVI46to365_data.h"
#include "NDVI46to365_initialize.h"
#include "islocalmax.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Function Declarations
static double rt_powd_snf(double u0, double u1);

// Function Definitions

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_powd_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    double d;
    double d1;
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

//
// Arguments    : double EXT09FEVI[545]
//                const double EXT09DMSK2[545]
//                const double ParamFit[4]
//                double *Date1
//                double *Date2
//                double *Date3
//                double *Date4
//                double *Date5
//                double *Date6
// Return Type  : void
//
void phen_6method(double EXT09FEVI[545], const double EXT09DMSK2[545], const
                  double ParamFit[4], double *Date1, double *Date2, double
                  *Date3, double *Date4, double *Date5, double *Date6)
{
  int idx;
  boolean_T ex;
  int k;
  boolean_T exitg1;
  double b_ex;
  int iyLead;
  double d;
  double work;
  double tmp2;
  boolean_T MethodTmp[365];
  double TMEP_tmp[364];
  boolean_T b_MethodTmp[364];
  double TMEP[363];
  boolean_T c_MethodTmp[363];
  double y[362];
  boolean_T d_MethodTmp[362];
  double a;
  double b_a;
  double c_a;
  double z[365];
  if (!isInitialized_NDVI46to365) {
    NDVI46to365_initialize();
  }

  for (idx = 0; idx < 545; idx++) {
    if (!(EXT09DMSK2[idx] != 0.0)) {
      EXT09FEVI[idx] = rtNaN;
    }
  }

  //  plot(MOD09TMEP)
  //  Method 1 : 0.2 amplitude thresholding
  ex = rtIsNaN(EXT09FEVI[90]);
  if (!ex) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 366)) {
      if (!rtIsNaN(EXT09FEVI[k + 89])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    b_ex = EXT09FEVI[90];
  } else {
    b_ex = EXT09FEVI[idx + 89];
    iyLead = idx + 1;
    for (k = iyLead; k < 366; k++) {
      d = EXT09FEVI[k + 89];
      if (b_ex < d) {
        b_ex = d;
      }
    }
  }

  if (!ex) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 366)) {
      if (!rtIsNaN(EXT09FEVI[k + 89])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    work = EXT09FEVI[90];
  } else {
    work = EXT09FEVI[idx + 89];
    iyLead = idx + 1;
    for (k = iyLead; k < 366; k++) {
      d = EXT09FEVI[k + 89];
      if (work > d) {
        work = d;
      }
    }
  }

  if (!ex) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 366)) {
      if (!rtIsNaN(EXT09FEVI[k + 89])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    tmp2 = EXT09FEVI[90];
  } else {
    tmp2 = EXT09FEVI[idx + 89];
    iyLead = idx + 1;
    for (k = iyLead; k < 366; k++) {
      d = EXT09FEVI[k + 89];
      if (tmp2 > d) {
        tmp2 = d;
      }
    }
  }

  for (idx = 0; idx < 365; idx++) {
    MethodTmp[idx] = (EXT09FEVI[idx + 90] > 0.2 * (b_ex - work) + tmp2);
  }

  idx = -1;
  ex = MethodTmp[0];
  for (k = 0; k < 364; k++) {
    if (static_cast<int>(ex) < static_cast<int>(MethodTmp[k + 1])) {
      ex = true;
      idx = k;
    }
  }

  *Date1 = static_cast<double>(idx) + 2.0;

  //  Method 2 : maximum changing rate
  idx = 1;
  iyLead = 0;
  work = EXT09FEVI[90];
  for (k = 0; k < 364; k++) {
    tmp2 = work;
    work = EXT09FEVI[idx + 90];
    TMEP_tmp[iyLead] = work - tmp2;
    idx++;
    iyLead++;
  }

  b_islocalmax(TMEP_tmp, b_MethodTmp);
  idx = -1;
  ex = b_MethodTmp[0];
  for (k = 0; k < 363; k++) {
    if (static_cast<int>(ex) < static_cast<int>(b_MethodTmp[k + 1])) {
      ex = true;
      idx = k;
    }
  }

  *Date2 = static_cast<double>(idx) + 2.0;

  //  Method 3 : maximum second-order derivative
  idx = 1;
  iyLead = 0;
  work = TMEP_tmp[0];
  for (k = 0; k < 363; k++) {
    tmp2 = work;
    work = TMEP_tmp[idx];
    TMEP[iyLead] = TMEP_tmp[idx] - tmp2;
    idx++;
    iyLead++;
  }

  c_islocalmax(TMEP, c_MethodTmp);
  idx = -1;
  ex = c_MethodTmp[0];
  for (k = 0; k < 362; k++) {
    if (static_cast<int>(ex) < static_cast<int>(c_MethodTmp[k + 1])) {
      ex = true;
      idx = k;
    }
  }

  *Date3 = static_cast<double>(idx) + 2.0;

  //  Method 4 : maximum relative increases in vegetation index
  for (iyLead = 0; iyLead < 364; iyLead++) {
    TMEP_tmp[iyLead] /= EXT09FEVI[iyLead + 90];
  }

  if (!rtIsNaN(TMEP_tmp[0])) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 365)) {
      if (!rtIsNaN(TMEP_tmp[k - 1])) {
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
    b_ex = TMEP_tmp[idx - 1];
    iyLead = idx + 1;
    for (k = iyLead; k < 365; k++) {
      d = TMEP_tmp[k - 1];
      if (b_ex < d) {
        b_ex = d;
        idx = k;
      }
    }
  }

  *Date4 = idx;

  //  Method 5 : maximum third-order derivative
  idx = 1;
  iyLead = 0;
  work = TMEP[0];
  for (k = 0; k < 362; k++) {
    tmp2 = work;
    work = TMEP[idx];
    y[iyLead] = TMEP[idx] - tmp2;
    idx++;
    iyLead++;
  }

  d_islocalmax(y, d_MethodTmp);
  idx = -1;
  ex = d_MethodTmp[0];
  for (k = 0; k < 361; k++) {
    if (static_cast<int>(ex) < static_cast<int>(d_MethodTmp[k + 1])) {
      ex = true;
      idx = k;
    }
  }

  *Date5 = static_cast<double>(idx) + 2.0;

  //  Methcod 6 : maximum changing rate in curvature
  a = ParamFit[2] * ParamFit[3];
  work = ParamFit[1] - ParamFit[0];
  b_a = rt_powd_snf(-ParamFit[3], 3.0) * work;
  c_a = -ParamFit[3] * -ParamFit[3] * (work * work);
  work *= -ParamFit[3];
  for (k = 0; k < 365; k++) {
    double d1;
    double d2;
    d = std::exp(a + -ParamFit[3] * (static_cast<double>(k) + 1.0));
    tmp2 = rt_powd_snf(d + 1.0, 3.0);
    b_ex = rt_powd_snf(d + 1.0, 4.0);
    d1 = work * d;
    d2 = rt_powd_snf(b_ex + d1 * d1, 2.5);
    b_ex += d1 * d1;
    d = b_a * d * (3.0 * d * (1.0 - d) * tmp2 * (2.0 * tmp2 + c_a * d) / d2 - (d
      + 1.0) * (d + 1.0) * ((2.0 * d + 1.0) - 5.0 * (d * d)) / rt_powd_snf(b_ex,
      1.5));
    z[k] = d;
  }

  e_islocalmax(z, MethodTmp);
  idx = -1;
  ex = MethodTmp[0];
  for (k = 0; k < 364; k++) {
    if (static_cast<int>(ex) < static_cast<int>(MethodTmp[k + 1])) {
      ex = true;
      idx = k;
    }
  }

  *Date6 = static_cast<double>(idx) + 2.0;
}

//
// File trailer for phen_6method.cpp
//
// [EOF]
//
