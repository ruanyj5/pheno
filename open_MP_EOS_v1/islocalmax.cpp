//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: islocalmax.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//

// Include Files
#include "islocalmax.h"
#include "NDVI46to365.h"
#include "isLocalExtrema.h"
#include "phen_6method.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions

//
// Arguments    : const double A[364]
//                boolean_T tf[364]
// Return Type  : void
//
void b_islocalmax(const double A[364], boolean_T tf[364])
{
  int i;
  boolean_T y;
  boolean_T isnanA[364];
  int k;
  boolean_T exitg1;
  double b_A[364];
  double varargout_2[364];
  int A_size[1];
  short tmp_data[364];
  double A_data[365];
  boolean_T b_tmp_data[365];
  int tmp_size[1];
  double c_tmp_data[365];
  int b_tmp_size[1];
  short d_tmp_data[364];
  for (i = 0; i < 364; i++) {
    isnanA[i] = rtIsNaN(A[i]);
  }

  y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 364)) {
    if (isnanA[k]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (!y) {
    int trueCount;
    trueCount = 0;
    k = 0;
    for (i = 0; i < 364; i++) {
      tf[i] = false;
      y = !isnanA[i];
      isnanA[i] = y;
      if (y) {
        trueCount++;
        tmp_data[k] = static_cast<short>(i + 1);
        k++;
      }
    }

    for (i = 0; i < trueCount; i++) {
      varargout_2[i] = A[tmp_data[i] - 1];
    }

    A_size[0] = trueCount;
    k = trueCount - 1;
    if (0 <= k) {
      std::memcpy(&A_data[0], &varargout_2[0], (k + 1) * sizeof(double));
    }

    c_doLocalMaxSearch(A_data, A_size, b_tmp_data, tmp_size, c_tmp_data,
                       b_tmp_size);
    k = 0;
    for (i = 0; i < 364; i++) {
      if (isnanA[i]) {
        d_tmp_data[k] = static_cast<short>(i + 1);
        k++;
      }
    }

    k = tmp_size[0];
    for (i = 0; i < k; i++) {
      tf[d_tmp_data[i] - 1] = b_tmp_data[i];
    }
  } else {
    std::memcpy(&b_A[0], &A[0], 364U * sizeof(double));
    d_doLocalMaxSearch(b_A, tf, varargout_2);
  }
}

//
// Arguments    : const double A[363]
//                boolean_T tf[363]
// Return Type  : void
//
void c_islocalmax(const double A[363], boolean_T tf[363])
{
  int i;
  boolean_T y;
  boolean_T isnanA[363];
  int k;
  boolean_T exitg1;
  double b_A[363];
  double varargout_2[363];
  int A_size[1];
  short tmp_data[363];
  double A_data[365];
  boolean_T b_tmp_data[365];
  int tmp_size[1];
  double c_tmp_data[365];
  int b_tmp_size[1];
  short d_tmp_data[363];
  for (i = 0; i < 363; i++) {
    isnanA[i] = rtIsNaN(A[i]);
  }

  y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 363)) {
    if (isnanA[k]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (!y) {
    int trueCount;
    trueCount = 0;
    k = 0;
    for (i = 0; i < 363; i++) {
      tf[i] = false;
      y = !isnanA[i];
      isnanA[i] = y;
      if (y) {
        trueCount++;
        tmp_data[k] = static_cast<short>(i + 1);
        k++;
      }
    }

    for (i = 0; i < trueCount; i++) {
      varargout_2[i] = A[tmp_data[i] - 1];
    }

    A_size[0] = trueCount;
    k = trueCount - 1;
    if (0 <= k) {
      std::memcpy(&A_data[0], &varargout_2[0], (k + 1) * sizeof(double));
    }

    c_doLocalMaxSearch(A_data, A_size, b_tmp_data, tmp_size, c_tmp_data,
                       b_tmp_size);
    k = 0;
    for (i = 0; i < 363; i++) {
      if (isnanA[i]) {
        d_tmp_data[k] = static_cast<short>(i + 1);
        k++;
      }
    }

    k = tmp_size[0];
    for (i = 0; i < k; i++) {
      tf[d_tmp_data[i] - 1] = b_tmp_data[i];
    }
  } else {
    std::memcpy(&b_A[0], &A[0], 363U * sizeof(double));
    e_doLocalMaxSearch(b_A, tf, varargout_2);
  }
}

//
// Arguments    : const double A[362]
//                boolean_T tf[362]
// Return Type  : void
//
void d_islocalmax(const double A[362], boolean_T tf[362])
{
  int i;
  boolean_T y;
  boolean_T isnanA[362];
  int k;
  boolean_T exitg1;
  double b_A[362];
  double varargout_2[362];
  int A_size[1];
  short tmp_data[362];
  double A_data[365];
  boolean_T b_tmp_data[365];
  int tmp_size[1];
  double c_tmp_data[365];
  int b_tmp_size[1];
  short d_tmp_data[362];
  for (i = 0; i < 362; i++) {
    isnanA[i] = rtIsNaN(A[i]);
  }

  y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 362)) {
    if (isnanA[k]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (!y) {
    int trueCount;
    trueCount = 0;
    k = 0;
    for (i = 0; i < 362; i++) {
      tf[i] = false;
      y = !isnanA[i];
      isnanA[i] = y;
      if (y) {
        trueCount++;
        tmp_data[k] = static_cast<short>(i + 1);
        k++;
      }
    }

    for (i = 0; i < trueCount; i++) {
      varargout_2[i] = A[tmp_data[i] - 1];
    }

    A_size[0] = trueCount;
    k = trueCount - 1;
    if (0 <= k) {
      std::memcpy(&A_data[0], &varargout_2[0], (k + 1) * sizeof(double));
    }

    c_doLocalMaxSearch(A_data, A_size, b_tmp_data, tmp_size, c_tmp_data,
                       b_tmp_size);
    k = 0;
    for (i = 0; i < 362; i++) {
      if (isnanA[i]) {
        d_tmp_data[k] = static_cast<short>(i + 1);
        k++;
      }
    }

    k = tmp_size[0];
    for (i = 0; i < k; i++) {
      tf[d_tmp_data[i] - 1] = b_tmp_data[i];
    }
  } else {
    std::memcpy(&b_A[0], &A[0], 362U * sizeof(double));
    f_doLocalMaxSearch(b_A, tf, varargout_2);
  }
}

//
// Arguments    : const double A[365]
//                boolean_T tf[365]
// Return Type  : void
//
void e_islocalmax(const double A[365], boolean_T tf[365])
{
  int i;
  boolean_T y;
  boolean_T isnanA[365];
  boolean_T exitg1;
  double b_A[365];
  double varargout_2[365];
  int A_size[1];
  boolean_T tmp_data[365];
  int tmp_size[1];
  int b_tmp_size[1];
  short b_tmp_data[365];
  short c_tmp_data[365];
  for (i = 0; i < 365; i++) {
    isnanA[i] = rtIsNaN(A[i]);
  }

  y = true;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 365)) {
    if (isnanA[i]) {
      y = false;
      exitg1 = true;
    } else {
      i++;
    }
  }

  if (!y) {
    int trueCount;
    int partialTrueCount;
    trueCount = 0;
    partialTrueCount = 0;
    for (i = 0; i < 365; i++) {
      tf[i] = false;
      y = !isnanA[i];
      isnanA[i] = y;
      if (y) {
        trueCount++;
        b_tmp_data[partialTrueCount] = static_cast<short>(i + 1);
        partialTrueCount++;
      }
    }

    A_size[0] = trueCount;
    for (partialTrueCount = 0; partialTrueCount < trueCount; partialTrueCount++)
    {
      varargout_2[partialTrueCount] = A[b_tmp_data[partialTrueCount] - 1];
    }

    c_doLocalMaxSearch(varargout_2, A_size, tmp_data, tmp_size, b_A, b_tmp_size);
    partialTrueCount = 0;
    for (i = 0; i < 365; i++) {
      if (isnanA[i]) {
        c_tmp_data[partialTrueCount] = static_cast<short>(i + 1);
        partialTrueCount++;
      }
    }

    i = tmp_size[0];
    for (partialTrueCount = 0; partialTrueCount < i; partialTrueCount++) {
      tf[c_tmp_data[partialTrueCount] - 1] = tmp_data[partialTrueCount];
    }
  } else {
    std::memcpy(&b_A[0], &A[0], 365U * sizeof(double));
    g_doLocalMaxSearch(b_A, tf, varargout_2);
  }
}

//
// Arguments    : const double A[365]
//                boolean_T tf[365]
// Return Type  : void
//
void islocalmax(const double A[365], boolean_T tf[365])
{
  int i;
  boolean_T y;
  boolean_T isnanA[365];
  boolean_T exitg1;
  double b_A[365];
  double varargout_2[365];
  int A_size[1];
  short tmp_data[365];
  boolean_T b_tmp_data[365];
  int tmp_size[1];
  double c_tmp_data[365];
  int b_tmp_size[1];
  short d_tmp_data[365];
  for (i = 0; i < 365; i++) {
    isnanA[i] = rtIsNaN(A[i]);
  }

  y = true;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 365)) {
    if (isnanA[i]) {
      y = false;
      exitg1 = true;
    } else {
      i++;
    }
  }

  if (!y) {
    int trueCount;
    int partialTrueCount;
    trueCount = 0;
    partialTrueCount = 0;
    for (i = 0; i < 365; i++) {
      tf[i] = false;
      y = !isnanA[i];
      isnanA[i] = y;
      if (y) {
        trueCount++;
        tmp_data[partialTrueCount] = static_cast<short>(i + 1);
        partialTrueCount++;
      }
    }

    A_size[0] = trueCount;
    for (partialTrueCount = 0; partialTrueCount < trueCount; partialTrueCount++)
    {
      varargout_2[partialTrueCount] = A[tmp_data[partialTrueCount] - 1];
    }

    for (partialTrueCount = 0; partialTrueCount < trueCount; partialTrueCount++)
    {
      b_A[partialTrueCount] = (static_cast<double>(tmp_data[partialTrueCount]) -
        1.0) + 1.0;
    }

    doLocalMaxSearch(varargout_2, A_size, b_A, b_tmp_data, tmp_size, c_tmp_data,
                     b_tmp_size);
    partialTrueCount = 0;
    for (i = 0; i < 365; i++) {
      if (isnanA[i]) {
        d_tmp_data[partialTrueCount] = static_cast<short>(i + 1);
        partialTrueCount++;
      }
    }

    i = tmp_size[0];
    for (partialTrueCount = 0; partialTrueCount < i; partialTrueCount++) {
      tf[d_tmp_data[partialTrueCount] - 1] = b_tmp_data[partialTrueCount];
    }
  } else {
    std::memcpy(&b_A[0], &A[0], 365U * sizeof(double));
    b_doLocalMaxSearch(b_A, tf, varargout_2);
  }
}

//
// File trailer for islocalmax.cpp
//
// [EOF]
//
