//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: isLocalExtrema.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//

// Include Files
#include "isLocalExtrema.h"
#include "NDVI46to365.h"
#include "diff.h"
#include "interp1.h"
#include "mean.h"
#include "nullAssignment.h"
#include "phen_6method.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include <cmath>
#include <cstring>

// Function Declarations
static void adjustFlatRegions(const double A_data[], const int A_size[1],
  boolean_T maxVals_data[], const int maxVals_size[1]);
static void b_adjustFlatRegions(const double A[365], boolean_T maxVals[365]);
static void b_filterByDistance(const double A[365], const double P[365],
  boolean_T maxVals[365]);
static void b_filterByProminence(const double A[365], boolean_T maxVals[365],
  double P[365], const boolean_T inflectionPts[365]);
static void b_findUniqueRanges(const double v[365], double left_data[], int
  left_size[1], double right_data[], int right_size[1]);
static void b_getAllLocalMax(const double A[365], boolean_T maxVals[365],
  boolean_T inflectionPts[365]);
static void b_restrictNumberOfExtrema(boolean_T maxVals[365], const double P[365]);
static void c_adjustFlatRegions(const double A[364], boolean_T maxVals[364]);
static void c_filterByProminence(const double A_data[], const int A_size[1],
  boolean_T maxVals_data[], const int maxVals_size[1], double P_data[], const
  boolean_T inflectionPts_data[]);
static void c_findUniqueRanges(const double v[364], double left_data[], int
  left_size[1], double right_data[], int right_size[1]);
static void c_getAllLocalMax(const double A[364], boolean_T maxVals[364],
  boolean_T inflectionPts[364]);
static void c_restrictNumberOfExtrema(const int A_size[1], boolean_T
  maxVals_data[], const int maxVals_size[1], const double P_data[]);
static void d_adjustFlatRegions(const double A[363], boolean_T maxVals[363]);
static void d_findUniqueRanges(const double v[363], double left_data[], int
  left_size[1], double right_data[], int right_size[1]);
static void d_getAllLocalMax(const double A[363], boolean_T maxVals[363],
  boolean_T inflectionPts[363]);
static void d_restrictNumberOfExtrema(boolean_T maxVals[364], const double P[364]);
static void e_adjustFlatRegions(const double A[362], boolean_T maxVals[362]);
static void e_findUniqueRanges(const double v[362], double left_data[], int
  left_size[1], double right_data[], int right_size[1]);
static void e_getAllLocalMax(const double A[362], boolean_T maxVals[362],
  boolean_T inflectionPts[362]);
static void e_restrictNumberOfExtrema(boolean_T maxVals[363], const double P[363]);
static void f_restrictNumberOfExtrema(boolean_T maxVals[362], const double P[362]);
static void filterByDistance(const double A_data[], const int A_size[1], const
  double P_data[], boolean_T maxVals_data[], const int maxVals_size[1], const
  double x_data[]);
static void filterByProminence(const double A_data[], const int A_size[1],
  boolean_T maxVals_data[], const int maxVals_size[1], double P_data[], const
  boolean_T inflectionPts_data[]);
static void findUniqueRanges(const double v_data[], const int v_size[1], double
  left_data[], int left_size[1], double right_data[], int right_size[1]);
static void g_restrictNumberOfExtrema(boolean_T maxVals[365], const double P[365]);
static void getAllLocalMax(const double A_data[], const int A_size[1], boolean_T
  maxVals_data[], int maxVals_size[1], boolean_T inflectionPts_data[], int
  inflectionPts_size[1]);
static void restrictNumberOfExtrema(const int A_size[1], boolean_T maxVals_data[],
  const int maxVals_size[1], const double P_data[]);

// Function Definitions

//
// Arguments    : const double A_data[]
//                const int A_size[1]
//                boolean_T maxVals_data[]
//                const int maxVals_size[1]
// Return Type  : void
//
static void adjustFlatRegions(const double A_data[], const int A_size[1],
  boolean_T maxVals_data[], const int maxVals_size[1])
{
  boolean_T colRngTF;
  int ctr;
  boolean_T exitg1;
  int i;
  int loop_ub;
  int b_A_size[1];
  double b_A_data[365];
  double leftRange_data[366];
  int leftRange_size[1];
  double rightRange_data[367];
  int rightRange_size[1];
  boolean_T flatRegion_data[366];
  boolean_T x_data[366];
  int ranges_size[2];
  short tmp_data[366];
  double ranges_data[732];
  int b_tmp_data[366];
  colRngTF = false;
  ctr = 1;
  exitg1 = false;
  while ((!exitg1) && (ctr <= maxVals_size[0])) {
    if (!maxVals_data[ctr - 1]) {
      ctr++;
    } else {
      colRngTF = true;
      exitg1 = true;
    }
  }

  ctr = 0;
  if (colRngTF) {
    ctr = 1;
  }

  i = (1 <= ctr) - 1;
  if (0 <= i) {
    loop_ub = A_size[0];
    b_A_size[0] = A_size[0];
    if (0 <= loop_ub - 1) {
      std::memcpy(&b_A_data[0], &A_data[0], loop_ub * sizeof(double));
    }
  }

  for (int k = 0; k <= i; k++) {
    findUniqueRanges(b_A_data, b_A_size, leftRange_data, leftRange_size,
                     rightRange_data, rightRange_size);
    loop_ub = rightRange_size[0];
    for (ctr = 0; ctr < loop_ub; ctr++) {
      flatRegion_data[ctr] = (rightRange_data[ctr] > leftRange_data[ctr]);
    }

    colRngTF = false;
    ctr = 1;
    exitg1 = false;
    while ((!exitg1) && (ctr <= loop_ub)) {
      if (!flatRegion_data[ctr - 1]) {
        ctr++;
      } else {
        colRngTF = true;
        exitg1 = true;
      }
    }

    if (colRngTF) {
      loop_ub = leftRange_size[0];
      for (ctr = 0; ctr < loop_ub; ctr++) {
        x_data[ctr] = (maxVals_data[static_cast<int>(leftRange_data[ctr]) - 1] &&
                       flatRegion_data[ctr]);
      }

      colRngTF = false;
      ctr = 1;
      exitg1 = false;
      while ((!exitg1) && (ctr <= loop_ub)) {
        if (!x_data[ctr - 1]) {
          ctr++;
        } else {
          colRngTF = true;
          exitg1 = true;
        }
      }

      if (colRngTF) {
        int trueCount;
        int b_i;
        ctr = leftRange_size[0] - 1;
        trueCount = 0;
        for (b_i = 0; b_i <= ctr; b_i++) {
          if (maxVals_data[static_cast<int>(leftRange_data[b_i]) - 1] &&
              flatRegion_data[b_i]) {
            trueCount++;
          }
        }

        loop_ub = 0;
        for (b_i = 0; b_i <= ctr; b_i++) {
          if (maxVals_data[static_cast<int>(leftRange_data[b_i]) - 1] &&
              flatRegion_data[b_i]) {
            tmp_data[loop_ub] = static_cast<short>(b_i + 1);
            loop_ub++;
          }
        }

        ranges_size[0] = trueCount;
        ranges_size[1] = 2;
        for (ctr = 0; ctr < trueCount; ctr++) {
          ranges_data[ctr] = leftRange_data[tmp_data[ctr] - 1];
        }

        for (ctr = 0; ctr < trueCount; ctr++) {
          ranges_data[ctr + trueCount] = rightRange_data[tmp_data[ctr] - 1];
        }

        for (ctr = 0; ctr < trueCount; ctr++) {
          b_tmp_data[ctr] = static_cast<int>(ranges_data[ctr]);
        }

        for (ctr = 0; ctr < trueCount; ctr++) {
          maxVals_data[b_tmp_data[ctr] - 1] = false;
        }

        mean(ranges_data, ranges_size, leftRange_data, leftRange_size);
        ctr = leftRange_size[0];
        for (loop_ub = 0; loop_ub < ctr; loop_ub++) {
          leftRange_data[loop_ub] = std::floor(leftRange_data[loop_ub]);
        }

        loop_ub = leftRange_size[0];
        for (ctr = 0; ctr < loop_ub; ctr++) {
          b_tmp_data[ctr] = static_cast<int>(leftRange_data[ctr]);
        }

        for (ctr = 0; ctr < loop_ub; ctr++) {
          maxVals_data[b_tmp_data[ctr] - 1] = true;
        }
      }
    }
  }
}

//
// Arguments    : const double A[365]
//                boolean_T maxVals[365]
// Return Type  : void
//
static void b_adjustFlatRegions(const double A[365], boolean_T maxVals[365])
{
  int ctr;
  boolean_T y;
  int k;
  boolean_T exitg1;
  int i;
  double leftRange_data[366];
  int leftRange_size[1];
  double rightRange_data[367];
  int rightRange_size[1];
  boolean_T flatRegion_data[366];
  boolean_T x_data[366];
  int ranges_size[2];
  short tmp_data[366];
  double ranges_data[732];
  int b_tmp_data[366];
  ctr = 0;
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= 364)) {
    if (maxVals[k]) {
      y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (y) {
    ctr = 1;
  }

  i = (1 <= ctr) - 1;
  for (k = 0; k <= i; k++) {
    int loop_ub;
    b_findUniqueRanges(A, leftRange_data, leftRange_size, rightRange_data,
                       rightRange_size);
    loop_ub = rightRange_size[0];
    for (ctr = 0; ctr < loop_ub; ctr++) {
      flatRegion_data[ctr] = (rightRange_data[ctr] > leftRange_data[ctr]);
    }

    y = false;
    ctr = 1;
    exitg1 = false;
    while ((!exitg1) && (ctr <= loop_ub)) {
      if (!flatRegion_data[ctr - 1]) {
        ctr++;
      } else {
        y = true;
        exitg1 = true;
      }
    }

    if (y) {
      loop_ub = leftRange_size[0];
      for (ctr = 0; ctr < loop_ub; ctr++) {
        x_data[ctr] = (maxVals[static_cast<int>(leftRange_data[ctr]) - 1] &&
                       flatRegion_data[ctr]);
      }

      y = false;
      ctr = 1;
      exitg1 = false;
      while ((!exitg1) && (ctr <= loop_ub)) {
        if (!x_data[ctr - 1]) {
          ctr++;
        } else {
          y = true;
          exitg1 = true;
        }
      }

      if (y) {
        int trueCount;
        int b_i;
        ctr = leftRange_size[0] - 1;
        trueCount = 0;
        for (b_i = 0; b_i <= ctr; b_i++) {
          if (maxVals[static_cast<int>(leftRange_data[b_i]) - 1] &&
              flatRegion_data[b_i]) {
            trueCount++;
          }
        }

        loop_ub = 0;
        for (b_i = 0; b_i <= ctr; b_i++) {
          if (maxVals[static_cast<int>(leftRange_data[b_i]) - 1] &&
              flatRegion_data[b_i]) {
            tmp_data[loop_ub] = static_cast<short>(b_i + 1);
            loop_ub++;
          }
        }

        ranges_size[0] = trueCount;
        ranges_size[1] = 2;
        for (ctr = 0; ctr < trueCount; ctr++) {
          ranges_data[ctr] = leftRange_data[tmp_data[ctr] - 1];
        }

        for (ctr = 0; ctr < trueCount; ctr++) {
          ranges_data[ctr + trueCount] = rightRange_data[tmp_data[ctr] - 1];
        }

        for (ctr = 0; ctr < trueCount; ctr++) {
          b_tmp_data[ctr] = static_cast<int>(ranges_data[ctr]);
        }

        for (ctr = 0; ctr < trueCount; ctr++) {
          maxVals[b_tmp_data[ctr] - 1] = false;
        }

        mean(ranges_data, ranges_size, leftRange_data, leftRange_size);
        ctr = leftRange_size[0];
        for (loop_ub = 0; loop_ub < ctr; loop_ub++) {
          leftRange_data[loop_ub] = std::floor(leftRange_data[loop_ub]);
        }

        loop_ub = leftRange_size[0];
        for (ctr = 0; ctr < loop_ub; ctr++) {
          b_tmp_data[ctr] = static_cast<int>(leftRange_data[ctr]);
        }

        for (ctr = 0; ctr < loop_ub; ctr++) {
          maxVals[b_tmp_data[ctr] - 1] = true;
        }
      }
    }
  }
}

//
// Arguments    : const double A[365]
//                const double P[365]
//                boolean_T maxVals[365]
// Return Type  : void
//
static void b_filterByDistance(const double A[365], const double P[365],
  boolean_T maxVals[365])
{
  int trueCount;
  int idx;
  int i;
  short locMaxima_data[365];
  short tmp_data[365];
  short leftIndices_data[365];
  short rightIndices_data[365];
  double left;
  int k;
  int right;
  int b_i;
  int leftIdx_size[2];
  double leftIdx_data[364];
  int maxVals_size[1];
  boolean_T maxVals_data[364];
  trueCount = 0;
  idx = 0;
  for (i = 0; i < 365; i++) {
    if (maxVals[i]) {
      trueCount++;
    }

    if (maxVals[i]) {
      tmp_data[idx] = static_cast<short>(i + 1);
      idx++;
    }
  }

  if (0 <= trueCount - 1) {
    std::memcpy(&locMaxima_data[0], &tmp_data[0], trueCount * sizeof(short));
  }

  if (0 <= trueCount - 1) {
    std::memcpy(&leftIndices_data[0], &locMaxima_data[0], trueCount * sizeof
                (short));
  }

  if (0 <= trueCount - 1) {
    std::memcpy(&rightIndices_data[0], &leftIndices_data[0], trueCount * sizeof
                (short));
  }

  for (i = 0; i < trueCount; i++) {
    k = tmp_data[i];
    b_i = tmp_data[i] - 1;
    if ((!rtIsInf(A[b_i])) && (!rtIsNaN(A[b_i]))) {
      while ((k < 364) && (A[k] == A[k - 1])) {
        k++;
      }

      rightIndices_data[i] = static_cast<short>(k);
    }
  }

  left = 1.0;
  right = 1;
  for (i = 0; i < trueCount; i++) {
    int exitg1;
    int i1;
    do {
      exitg1 = 0;
      b_i = static_cast<int>(left) - 1;
      if (leftIndices_data[i] - rightIndices_data[b_i] >= 60) {
        left++;
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);

    if (static_cast<double>(i) + 1.0 > right) {
      right = i + 1;
    }

    while ((right <= static_cast<double>(trueCount) - 1.0) &&
           (leftIndices_data[right] - rightIndices_data[i] < 60)) {
      right++;
    }

    i1 = tmp_data[i] - 1;
    if ((!rtIsInf(A[i1])) && (!rtIsNaN(A[i1]))) {
      int i2;
      int i3;
      int loop_ub;
      if (left > (static_cast<double>(i) + 1.0) - 1.0) {
        b_i = 0;
        i2 = 0;
        i3 = 0;
        idx = 0;
      } else {
        i2 = i;
        i3 = b_i;
        idx = i;
      }

      leftIdx_size[0] = 1;
      loop_ub = i2 - b_i;
      leftIdx_size[1] = loop_ub;
      for (i2 = 0; i2 < loop_ub; i2++) {
        leftIdx_data[i2] = locMaxima_data[b_i + i2];
      }

      loop_ub = idx - i3;
      maxVals_size[0] = loop_ub;
      for (b_i = 0; b_i < loop_ub; b_i++) {
        maxVals_data[b_i] = !maxVals[locMaxima_data[i3 + b_i] - 1];
      }

      nullAssignment(leftIdx_data, leftIdx_size, maxVals_data, maxVals_size);
      b_i = leftIdx_size[1];
      if (leftIdx_size[1] != 0) {
        double rightMax;
        if (leftIdx_size[1] <= 2) {
          if (leftIdx_size[1] == 1) {
            rightMax = P[static_cast<int>(leftIdx_data[0]) - 1];
          } else {
            b_i = static_cast<int>(leftIdx_data[0]) - 1;
            i2 = static_cast<int>(leftIdx_data[1]) - 1;
            if ((P[b_i] < P[i2]) || (rtIsNaN(P[b_i]) && (!rtIsNaN(P[i2])))) {
              rightMax = P[i2];
            } else {
              rightMax = P[b_i];
            }
          }
        } else {
          i2 = static_cast<int>(leftIdx_data[0]) - 1;
          if (!rtIsNaN(P[i2])) {
            idx = 1;
          } else {
            boolean_T exitg2;
            idx = 0;
            k = 2;
            exitg2 = false;
            while ((!exitg2) && (k <= leftIdx_size[1])) {
              if (!rtIsNaN(P[static_cast<int>(leftIdx_data[k - 1]) - 1])) {
                idx = k;
                exitg2 = true;
              } else {
                k++;
              }
            }
          }

          if (idx == 0) {
            rightMax = P[i2];
          } else {
            rightMax = P[static_cast<int>(leftIdx_data[idx - 1]) - 1];
            i2 = idx + 1;
            for (k = i2; k <= b_i; k++) {
              i3 = static_cast<int>(leftIdx_data[k - 1]) - 1;
              if (rightMax < P[i3]) {
                rightMax = P[i3];
              }
            }
          }
        }

        if (rightMax >= P[i1]) {
          maxVals[i1] = false;
        }
      } else {
        if ((static_cast<double>(i) + 1.0) + 1.0 > right) {
          b_i = -1;
          i2 = 0;
        } else {
          b_i = i;
          i2 = right;
        }

        if (static_cast<short>((i2 - b_i) - 1) != 0) {
          double rightMax;
          if ((static_cast<double>(i) + 1.0) + 1.0 > right) {
            b_i = -1;
            i2 = -1;
          } else {
            b_i = i;
            i2 = right - 1;
          }

          loop_ub = i2 - b_i;
          if (loop_ub <= 2) {
            if (loop_ub == 1) {
              rightMax = P[locMaxima_data[b_i + 1] - 1];
            } else {
              i2 = locMaxima_data[b_i + 1] - 1;
              b_i = locMaxima_data[b_i + 2] - 1;
              if ((P[i2] < P[b_i]) || (rtIsNaN(P[i2]) && (!rtIsNaN(P[b_i])))) {
                rightMax = P[b_i];
              } else {
                rightMax = P[i2];
              }
            }
          } else {
            i2 = locMaxima_data[b_i + 1] - 1;
            if (!rtIsNaN(P[i2])) {
              idx = 1;
            } else {
              boolean_T exitg2;
              idx = 0;
              k = 2;
              exitg2 = false;
              while ((!exitg2) && (k <= loop_ub)) {
                if (!rtIsNaN(P[locMaxima_data[b_i + k] - 1])) {
                  idx = k;
                  exitg2 = true;
                } else {
                  k++;
                }
              }
            }

            if (idx == 0) {
              rightMax = P[i2];
            } else {
              rightMax = P[locMaxima_data[b_i + idx] - 1];
              i2 = idx + 1;
              for (k = i2; k <= loop_ub; k++) {
                i3 = locMaxima_data[b_i + k] - 1;
                if (rightMax < P[i3]) {
                  rightMax = P[i3];
                }
              }
            }
          }

          if (rightMax > P[i1]) {
            maxVals[i1] = false;
          }
        }
      }
    }
  }
}

//
// Arguments    : const double A[365]
//                boolean_T maxVals[365]
//                double P[365]
//                const boolean_T inflectionPts[365]
// Return Type  : void
//
static void b_filterByProminence(const double A[365], boolean_T maxVals[365],
  double P[365], const boolean_T inflectionPts[365])
{
  int trueCount;
  int partialTrueCount;
  int i;
  short tmp_data[365];
  boolean_T isLocMax[365];
  trueCount = 0;
  partialTrueCount = 0;
  for (i = 0; i < 365; i++) {
    if (maxVals[i] || inflectionPts[i]) {
      trueCount++;
    }

    if (maxVals[i] || inflectionPts[i]) {
      tmp_data[partialTrueCount] = static_cast<short>(i + 1);
      partialTrueCount++;
    }

    isLocMax[i] = maxVals[i];
  }

  for (i = 0; i < trueCount; i++) {
    partialTrueCount = tmp_data[i] - 1;
    if (isLocMax[partialTrueCount]) {
      double localMaxValue;
      localMaxValue = A[partialTrueCount];
      if (rtIsInf(A[partialTrueCount]) || rtIsNaN(A[partialTrueCount])) {
        P[partialTrueCount] = rtInf;
      } else {
        double localMins_idx_0;
        double localMins_idx_1;
        int left;
        int right;
        int b_i;
        localMins_idx_0 = A[partialTrueCount];
        localMins_idx_1 = A[partialTrueCount];
        left = i - 1;
        right = i + 1;
        int exitg3;
        do {
          exitg3 = 0;
          if (left + 1 > 0) {
            b_i = tmp_data[left] - 1;
            if (!isLocMax[b_i]) {
              if ((!(localMins_idx_0 < A[b_i])) && (!rtIsNaN(A[b_i]))) {
                localMins_idx_0 = A[b_i];
              }

              left--;
            } else if (A[b_i] > localMaxValue) {
              exitg3 = 1;
            } else {
              left--;
            }
          } else {
            exitg3 = 2;
          }
        } while (exitg3 == 0);

        int exitg2;
        do {
          exitg2 = 0;
          if (right + 1 <= trueCount) {
            b_i = tmp_data[right] - 1;
            if (!isLocMax[b_i]) {
              if ((!(localMins_idx_1 < A[b_i])) && (!rtIsNaN(A[b_i]))) {
                localMins_idx_1 = A[b_i];
              }

              right++;
            } else if (A[b_i] > localMaxValue) {
              exitg2 = 1;
            } else {
              right++;
            }
          } else {
            exitg2 = 1;
          }
        } while (exitg2 == 0);

        if ((localMins_idx_0 < localMins_idx_1) || (rtIsNaN(localMins_idx_0) &&
             (!rtIsNaN(localMins_idx_1)))) {
          localMins_idx_0 = localMins_idx_1;
        }

        P[partialTrueCount] = A[partialTrueCount] - localMins_idx_0;
        maxVals[partialTrueCount] = (P[partialTrueCount] >= 0.02);
      }
    }
  }
}

//
// Arguments    : const double v[365]
//                double left_data[]
//                int left_size[1]
//                double right_data[]
//                int right_size[1]
// Return Type  : void
//
static void b_findUniqueRanges(const double v[365], double left_data[], int
  left_size[1], double right_data[], int right_size[1])
{
  int ixLead;
  int iyLead;
  double work;
  int m;
  short idxTemp[365];
  double d[364];
  ixLead = 1;
  iyLead = 0;
  work = v[0];
  for (m = 0; m < 364; m++) {
    double tmp2;
    tmp2 = work;
    work = v[ixLead];
    d[iyLead] = v[ixLead] - tmp2;
    ixLead++;
    iyLead++;
  }

  std::memset(&idxTemp[0], 0, 365U * sizeof(short));
  work = 1.0;
  for (ixLead = 0; ixLead < 364; ixLead++) {
    if (d[ixLead] != 0.0) {
      idxTemp[static_cast<int>(work) - 1] = static_cast<short>(ixLead + 1);
      work++;
    }
  }

  if (1.0 > work - 1.0) {
    ixLead = 0;
  } else {
    ixLead = static_cast<int>(work - 1.0);
  }

  left_size[0] = ixLead + 1;
  left_data[0] = 1.0;
  for (iyLead = 0; iyLead < ixLead; iyLead++) {
    left_data[iyLead + 1] = static_cast<double>(idxTemp[iyLead]) + 1.0;
  }

  if (2 > left_size[0]) {
    iyLead = 0;
    m = 0;
  } else {
    iyLead = 1;
    m = left_size[0];
  }

  ixLead = m - iyLead;
  right_size[0] = ixLead + 1;
  for (m = 0; m < ixLead; m++) {
    right_data[m] = left_data[iyLead + m] - 1.0;
  }

  right_data[ixLead] = 365.0;
}

//
// Arguments    : const double A[365]
//                boolean_T maxVals[365]
//                boolean_T inflectionPts[365]
// Return Type  : void
//
static void b_getAllLocalMax(const double A[365], boolean_T maxVals[365],
  boolean_T inflectionPts[365])
{
  int ixLead;
  int iyLead;
  double work;
  int indEnd;
  double tmp2;
  double s[364];
  boolean_T y;
  boolean_T nanMask[365];
  boolean_T exitg1;
  boolean_T x[364];
  double b[364];
  int i;
  boolean_T uniquePts[365];
  double b_y[363];
  int tmp_size[2];
  short tmp_data[364];
  int s_size[1];
  double b_tmp_data[364];
  short c_tmp_data[364];
  int b_tmp_size[2];
  double s_data[364];
  double d_tmp_data[364];
  double e_tmp_data[364];
  int c_tmp_size[2];
  ixLead = 1;
  iyLead = 0;
  work = A[0];
  for (indEnd = 0; indEnd < 364; indEnd++) {
    tmp2 = work;
    work = A[ixLead];
    s[iyLead] = A[ixLead] - tmp2;
    ixLead++;
    iyLead++;
  }

  for (iyLead = 0; iyLead < 364; iyLead++) {
    work = s[iyLead];
    if (s[iyLead] < 0.0) {
      work = -1.0;
    } else if (s[iyLead] > 0.0) {
      work = 1.0;
    } else {
      if (s[iyLead] == 0.0) {
        work = 0.0;
      }
    }

    s[iyLead] = work;
  }

  for (ixLead = 0; ixLead < 365; ixLead++) {
    nanMask[ixLead] = rtIsNaN(A[ixLead]);
  }

  y = false;
  iyLead = 0;
  exitg1 = false;
  while ((!exitg1) && (iyLead <= 364)) {
    if (nanMask[iyLead]) {
      y = true;
      exitg1 = true;
    } else {
      iyLead++;
    }
  }

  if (y) {
    for (ixLead = 0; ixLead < 364; ixLead++) {
      if (nanMask[ixLead]) {
        s[ixLead] = -1.0;
      }

      if ((!nanMask[ixLead]) && nanMask[ixLead + 1]) {
        s[ixLead] = 1.0;
      }
    }
  }

  y = true;
  iyLead = 0;
  exitg1 = false;
  while ((!exitg1) && (iyLead <= 363)) {
    if (s[iyLead] == 0.0) {
      y = false;
      exitg1 = true;
    } else {
      iyLead++;
    }
  }

  if (!y) {
    for (ixLead = 0; ixLead < 364; ixLead++) {
      b[ixLead] = s[ixLead];
      x[ixLead] = (s[ixLead] != 0.0);
    }

    ixLead = x[0];
    for (iyLead = 0; iyLead < 363; iyLead++) {
      ixLead += x[iyLead + 1];
    }

    if (ixLead > 1) {
      int trueCount;
      int b_trueCount;
      trueCount = 0;
      iyLead = 0;
      b_trueCount = 0;
      indEnd = 0;
      for (ixLead = 0; ixLead < 364; ixLead++) {
        if (s[ixLead] != 0.0) {
          trueCount++;
          tmp_data[iyLead] = static_cast<short>(ixLead + 1);
          iyLead++;
        }

        if (!(s[ixLead] != 0.0)) {
          b_trueCount++;
          c_tmp_data[indEnd] = static_cast<short>(ixLead + 1);
          indEnd++;
        }
      }

      tmp_size[0] = 1;
      tmp_size[1] = trueCount;
      for (i = 0; i < trueCount; i++) {
        b_tmp_data[i] = (static_cast<double>(tmp_data[i]) - 1.0) + 1.0;
      }

      s_size[0] = trueCount;
      for (i = 0; i < trueCount; i++) {
        s_data[i] = s[tmp_data[i] - 1];
      }

      b_tmp_size[0] = 1;
      b_tmp_size[1] = b_trueCount;
      for (i = 0; i < b_trueCount; i++) {
        d_tmp_data[i] = (static_cast<double>(c_tmp_data[i]) - 1.0) + 1.0;
      }

      interp1(b_tmp_data, tmp_size, s_data, s_size, d_tmp_data, b_tmp_size,
              e_tmp_data, c_tmp_size);
      iyLead = 0;
      for (ixLead = 0; ixLead < 364; ixLead++) {
        if (!(b[ixLead] != 0.0)) {
          b[ixLead] = e_tmp_data[iyLead];
          iyLead++;
        }
      }
    }

    work = 0.0;
    ixLead = 0;
    indEnd = 363;
    for (iyLead = 0; iyLead < 364; iyLead++) {
      if (s[iyLead] != 0.0) {
        if (work == 0.0) {
          ixLead = iyLead;
        }

        indEnd = iyLead;
        work++;
      }
    }

    if (1 > ixLead) {
      iyLead = 0;
    } else {
      iyLead = ixLead;
    }

    for (i = 0; i < iyLead; i++) {
      b[i] = s[ixLead];
    }

    if (indEnd + 2 > 364) {
      i = -1;
      ixLead = -1;
    } else {
      i = indEnd;
      ixLead = 363;
    }

    iyLead = ixLead - i;
    for (ixLead = 0; ixLead < iyLead; ixLead++) {
      b[(i + ixLead) + 1] = s[indEnd];
    }

    std::memcpy(&s[0], &b[0], 364U * sizeof(double));
  }

  std::memset(&maxVals[0], 0, 365U * sizeof(boolean_T));
  ixLead = 1;
  iyLead = 0;
  work = s[0];
  for (indEnd = 0; indEnd < 363; indEnd++) {
    tmp2 = work;
    work = s[ixLead];
    b_y[iyLead] = s[ixLead] - tmp2;
    ixLead++;
    iyLead++;
  }

  for (i = 0; i < 363; i++) {
    maxVals[i + 1] = (b_y[i] < 0.0);
  }

  uniquePts[0] = true;
  for (ixLead = 0; ixLead < 364; ixLead++) {
    uniquePts[ixLead + 1] = (A[ixLead + 1] != A[ixLead]);
  }

  y = false;
  iyLead = 0;
  exitg1 = false;
  while ((!exitg1) && (iyLead <= 364)) {
    if (nanMask[iyLead]) {
      y = true;
      exitg1 = true;
    } else {
      iyLead++;
    }
  }

  if (y) {
    nanMask[0] = uniquePts[0];
    for (ixLead = 0; ixLead < 364; ixLead++) {
      nanMask[ixLead + 1] = (uniquePts[ixLead + 1] && ((!rtIsNaN(A[ixLead + 1]))
        || (!rtIsNaN(A[ixLead]))));
    }

    std::memcpy(&uniquePts[0], &nanMask[0], 365U * sizeof(boolean_T));
  }

  inflectionPts[0] = true;
  for (ixLead = 0; ixLead < 363; ixLead++) {
    inflectionPts[ixLead + 1] = ((s[ixLead] != s[ixLead + 1]) &&
      uniquePts[ixLead + 1]);
  }

  inflectionPts[364] = true;
}

//
// Arguments    : boolean_T maxVals[365]
//                const double P[365]
// Return Type  : void
//
static void b_restrictNumberOfExtrema(boolean_T maxVals[365], const double P[365])
{
  int trueCount;
  int partialTrueCount;
  int i;
  short locMaxima_data[365];
  short tmp_data[365];
  int x_size[1];
  double x_data[365];
  int iidx_data[365];
  int iidx_size[1];
  trueCount = 0;
  partialTrueCount = 0;
  for (i = 0; i < 365; i++) {
    if (maxVals[i]) {
      trueCount++;
    }

    if (maxVals[i]) {
      tmp_data[partialTrueCount] = static_cast<short>(i + 1);
      partialTrueCount++;
    }
  }

  if (0 <= trueCount - 1) {
    std::memcpy(&locMaxima_data[0], &tmp_data[0], trueCount * sizeof(short));
  }

  x_size[0] = trueCount;
  for (i = 0; i < trueCount; i++) {
    x_data[i] = P[locMaxima_data[i] - 1];
  }

  sort(x_data, x_size, iidx_data, iidx_size);
  partialTrueCount = iidx_size[0];
  for (i = 0; i < partialTrueCount; i++) {
    x_data[i] = iidx_data[i];
  }

  if (4 > iidx_size[0]) {
    i = 0;
    trueCount = 0;
  } else {
    i = 3;
    trueCount = iidx_size[0];
  }

  partialTrueCount = trueCount - i;
  for (trueCount = 0; trueCount < partialTrueCount; trueCount++) {
    iidx_data[trueCount] = locMaxima_data[static_cast<int>(x_data[i + trueCount])
      - 1];
  }

  for (i = 0; i < partialTrueCount; i++) {
    maxVals[iidx_data[i] - 1] = false;
  }
}

//
// Arguments    : const double A[364]
//                boolean_T maxVals[364]
// Return Type  : void
//
static void c_adjustFlatRegions(const double A[364], boolean_T maxVals[364])
{
  int ctr;
  boolean_T y;
  int k;
  boolean_T exitg1;
  int i;
  double leftRange_data[365];
  int leftRange_size[1];
  double rightRange_data[366];
  int rightRange_size[1];
  boolean_T flatRegion_data[365];
  boolean_T x_data[366];
  int result_size[2];
  short tmp_data[365];
  double result_data[732];
  int b_tmp_data[365];
  ctr = 0;
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= 363)) {
    if (maxVals[k]) {
      y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (y) {
    ctr = 1;
  }

  i = (1 <= ctr) - 1;
  for (k = 0; k <= i; k++) {
    int loop_ub;
    c_findUniqueRanges(A, leftRange_data, leftRange_size, rightRange_data,
                       rightRange_size);
    loop_ub = rightRange_size[0];
    for (ctr = 0; ctr < loop_ub; ctr++) {
      flatRegion_data[ctr] = (rightRange_data[ctr] > leftRange_data[ctr]);
    }

    y = false;
    ctr = 1;
    exitg1 = false;
    while ((!exitg1) && (ctr <= loop_ub)) {
      if (!flatRegion_data[ctr - 1]) {
        ctr++;
      } else {
        y = true;
        exitg1 = true;
      }
    }

    if (y) {
      loop_ub = leftRange_size[0];
      for (ctr = 0; ctr < loop_ub; ctr++) {
        x_data[ctr] = (maxVals[static_cast<int>(leftRange_data[ctr]) - 1] &&
                       flatRegion_data[ctr]);
      }

      y = false;
      ctr = 1;
      exitg1 = false;
      while ((!exitg1) && (ctr <= loop_ub)) {
        if (!x_data[ctr - 1]) {
          ctr++;
        } else {
          y = true;
          exitg1 = true;
        }
      }

      if (y) {
        int trueCount;
        int b_i;
        ctr = leftRange_size[0] - 1;
        trueCount = 0;
        for (b_i = 0; b_i <= ctr; b_i++) {
          if (maxVals[static_cast<int>(leftRange_data[b_i]) - 1] &&
              flatRegion_data[b_i]) {
            trueCount++;
          }
        }

        loop_ub = 0;
        for (b_i = 0; b_i <= ctr; b_i++) {
          if (maxVals[static_cast<int>(leftRange_data[b_i]) - 1] &&
              flatRegion_data[b_i]) {
            tmp_data[loop_ub] = static_cast<short>(b_i + 1);
            loop_ub++;
          }
        }

        result_size[0] = trueCount;
        result_size[1] = 2;
        for (ctr = 0; ctr < trueCount; ctr++) {
          result_data[ctr] = leftRange_data[tmp_data[ctr] - 1];
        }

        for (ctr = 0; ctr < trueCount; ctr++) {
          result_data[ctr + trueCount] = rightRange_data[tmp_data[ctr] - 1];
        }

        for (ctr = 0; ctr < trueCount; ctr++) {
          b_tmp_data[ctr] = static_cast<int>(result_data[ctr]);
        }

        for (ctr = 0; ctr < trueCount; ctr++) {
          maxVals[b_tmp_data[ctr] - 1] = false;
        }

        mean(result_data, result_size, rightRange_data, rightRange_size);
        ctr = rightRange_size[0];
        for (loop_ub = 0; loop_ub < ctr; loop_ub++) {
          rightRange_data[loop_ub] = std::floor(rightRange_data[loop_ub]);
        }

        loop_ub = rightRange_size[0];
        for (ctr = 0; ctr < loop_ub; ctr++) {
          b_tmp_data[ctr] = static_cast<int>(rightRange_data[ctr]);
        }

        for (ctr = 0; ctr < loop_ub; ctr++) {
          maxVals[b_tmp_data[ctr] - 1] = true;
        }
      }
    }
  }
}

//
// Arguments    : const double A_data[]
//                const int A_size[1]
//                boolean_T maxVals_data[]
//                const int maxVals_size[1]
//                double P_data[]
//                const boolean_T inflectionPts_data[]
// Return Type  : void
//
static void c_filterByProminence(const double A_data[], const int A_size[1],
  boolean_T maxVals_data[], const int maxVals_size[1], double P_data[], const
  boolean_T inflectionPts_data[])
{
  int idx_size_idx_1;
  int left;
  int i;
  int trueCount;
  unsigned int idx_data[365];
  int right;
  int b_i;
  boolean_T isLocMax_data[365];
  short tmp_data[365];
  if (A_size[0] < 1) {
    idx_size_idx_1 = 0;
  } else {
    idx_size_idx_1 = A_size[0];
    left = A_size[0] - 1;
    for (i = 0; i <= left; i++) {
      idx_data[i] = static_cast<unsigned int>(i + 1);
    }
  }

  left = maxVals_size[0] - 1;
  trueCount = 0;
  right = 0;
  for (b_i = 0; b_i <= left; b_i++) {
    if (maxVals_data[b_i] || inflectionPts_data[b_i]) {
      trueCount++;
    }

    if (maxVals_data[b_i] || inflectionPts_data[b_i]) {
      tmp_data[right] = static_cast<short>(b_i + 1);
      right++;
    }
  }

  for (i = 0; i < idx_size_idx_1; i++) {
    isLocMax_data[i] = maxVals_data[static_cast<int>(idx_data[i]) - 1];
  }

  for (b_i = 0; b_i < trueCount; b_i++) {
    i = static_cast<int>(idx_data[tmp_data[b_i] - 1]) - 1;
    if (isLocMax_data[i]) {
      double localMaxValue;
      localMaxValue = A_data[i];
      if (rtIsInf(A_data[i]) || rtIsNaN(A_data[i])) {
        P_data[i] = rtInf;
      } else {
        double localMins_idx_0;
        double localMins_idx_1;
        localMins_idx_0 = A_data[i];
        localMins_idx_1 = A_data[i];
        left = b_i - 1;
        right = b_i + 1;
        int exitg3;
        do {
          exitg3 = 0;
          if (left + 1 > 0) {
            idx_size_idx_1 = static_cast<int>(idx_data[tmp_data[left] - 1]) - 1;
            if (!isLocMax_data[idx_size_idx_1]) {
              if ((!(localMins_idx_0 < A_data[idx_size_idx_1])) && (!rtIsNaN
                   (A_data[idx_size_idx_1]))) {
                localMins_idx_0 = A_data[idx_size_idx_1];
              }

              left--;
            } else if (A_data[idx_size_idx_1] > localMaxValue) {
              exitg3 = 1;
            } else {
              left--;
            }
          } else {
            exitg3 = 2;
          }
        } while (exitg3 == 0);

        int exitg2;
        do {
          exitg2 = 0;
          if (right + 1 <= trueCount) {
            idx_size_idx_1 = static_cast<int>(idx_data[tmp_data[right] - 1]) - 1;
            if (!isLocMax_data[idx_size_idx_1]) {
              if ((!(localMins_idx_1 < A_data[idx_size_idx_1])) && (!rtIsNaN
                   (A_data[idx_size_idx_1]))) {
                localMins_idx_1 = A_data[idx_size_idx_1];
              }

              right++;
            } else if (A_data[idx_size_idx_1] > localMaxValue) {
              exitg2 = 1;
            } else {
              right++;
            }
          } else {
            exitg2 = 1;
          }
        } while (exitg2 == 0);

        if ((localMins_idx_0 < localMins_idx_1) || (rtIsNaN(localMins_idx_0) &&
             (!rtIsNaN(localMins_idx_1)))) {
          localMins_idx_0 = localMins_idx_1;
        }

        P_data[i] = A_data[i] - localMins_idx_0;
        maxVals_data[i] = (P_data[i] >= 0.0);
      }
    }
  }
}

//
// Arguments    : const double v[364]
//                double left_data[]
//                int left_size[1]
//                double right_data[]
//                int right_size[1]
// Return Type  : void
//
static void c_findUniqueRanges(const double v[364], double left_data[], int
  left_size[1], double right_data[], int right_size[1])
{
  int ixLead;
  int iyLead;
  double work;
  int m;
  short idxTemp[364];
  double d[363];
  ixLead = 1;
  iyLead = 0;
  work = v[0];
  for (m = 0; m < 363; m++) {
    double tmp2;
    tmp2 = work;
    work = v[ixLead];
    d[iyLead] = v[ixLead] - tmp2;
    ixLead++;
    iyLead++;
  }

  std::memset(&idxTemp[0], 0, 364U * sizeof(short));
  work = 1.0;
  for (ixLead = 0; ixLead < 363; ixLead++) {
    if (d[ixLead] != 0.0) {
      idxTemp[static_cast<int>(work) - 1] = static_cast<short>(ixLead + 1);
      work++;
    }
  }

  if (1.0 > work - 1.0) {
    ixLead = 0;
  } else {
    ixLead = static_cast<int>(work - 1.0);
  }

  left_size[0] = ixLead + 1;
  left_data[0] = 1.0;
  for (iyLead = 0; iyLead < ixLead; iyLead++) {
    left_data[iyLead + 1] = static_cast<double>(idxTemp[iyLead]) + 1.0;
  }

  if (2 > left_size[0]) {
    iyLead = 0;
    m = 0;
  } else {
    iyLead = 1;
    m = left_size[0];
  }

  ixLead = m - iyLead;
  right_size[0] = ixLead + 1;
  for (m = 0; m < ixLead; m++) {
    right_data[m] = left_data[iyLead + m] - 1.0;
  }

  right_data[ixLead] = 364.0;
}

//
// Arguments    : const double A[364]
//                boolean_T maxVals[364]
//                boolean_T inflectionPts[364]
// Return Type  : void
//
static void c_getAllLocalMax(const double A[364], boolean_T maxVals[364],
  boolean_T inflectionPts[364])
{
  int ixLead;
  int iyLead;
  double work;
  int indEnd;
  double tmp2;
  double s[363];
  boolean_T y;
  boolean_T nanMask[364];
  boolean_T exitg1;
  boolean_T x[363];
  double b[363];
  int i;
  boolean_T uniquePts[364];
  double b_y[362];
  int tmp_size[2];
  short tmp_data[363];
  int s_size[1];
  double b_tmp_data[363];
  short c_tmp_data[363];
  int b_tmp_size[2];
  double s_data[363];
  double d_tmp_data[363];
  double e_tmp_data[364];
  int c_tmp_size[2];
  ixLead = 1;
  iyLead = 0;
  work = A[0];
  for (indEnd = 0; indEnd < 363; indEnd++) {
    tmp2 = work;
    work = A[ixLead];
    s[iyLead] = A[ixLead] - tmp2;
    ixLead++;
    iyLead++;
  }

  for (iyLead = 0; iyLead < 363; iyLead++) {
    work = s[iyLead];
    if (s[iyLead] < 0.0) {
      work = -1.0;
    } else if (s[iyLead] > 0.0) {
      work = 1.0;
    } else {
      if (s[iyLead] == 0.0) {
        work = 0.0;
      }
    }

    s[iyLead] = work;
  }

  for (ixLead = 0; ixLead < 364; ixLead++) {
    nanMask[ixLead] = rtIsNaN(A[ixLead]);
  }

  y = false;
  iyLead = 0;
  exitg1 = false;
  while ((!exitg1) && (iyLead <= 363)) {
    if (nanMask[iyLead]) {
      y = true;
      exitg1 = true;
    } else {
      iyLead++;
    }
  }

  if (y) {
    for (ixLead = 0; ixLead < 363; ixLead++) {
      if (nanMask[ixLead]) {
        s[ixLead] = -1.0;
      }

      if ((!nanMask[ixLead]) && nanMask[ixLead + 1]) {
        s[ixLead] = 1.0;
      }
    }
  }

  y = true;
  iyLead = 0;
  exitg1 = false;
  while ((!exitg1) && (iyLead <= 362)) {
    if (s[iyLead] == 0.0) {
      y = false;
      exitg1 = true;
    } else {
      iyLead++;
    }
  }

  if (!y) {
    for (ixLead = 0; ixLead < 363; ixLead++) {
      b[ixLead] = s[ixLead];
      x[ixLead] = (s[ixLead] != 0.0);
    }

    ixLead = x[0];
    for (iyLead = 0; iyLead < 362; iyLead++) {
      ixLead += x[iyLead + 1];
    }

    if (ixLead > 1) {
      int trueCount;
      int b_trueCount;
      trueCount = 0;
      iyLead = 0;
      b_trueCount = 0;
      indEnd = 0;
      for (ixLead = 0; ixLead < 363; ixLead++) {
        if (s[ixLead] != 0.0) {
          trueCount++;
          tmp_data[iyLead] = static_cast<short>(ixLead + 1);
          iyLead++;
        }

        if (!(s[ixLead] != 0.0)) {
          b_trueCount++;
          c_tmp_data[indEnd] = static_cast<short>(ixLead + 1);
          indEnd++;
        }
      }

      tmp_size[0] = 1;
      tmp_size[1] = trueCount;
      for (i = 0; i < trueCount; i++) {
        b_tmp_data[i] = (static_cast<double>(tmp_data[i]) - 1.0) + 1.0;
      }

      s_size[0] = trueCount;
      for (i = 0; i < trueCount; i++) {
        s_data[i] = s[tmp_data[i] - 1];
      }

      b_tmp_size[0] = 1;
      b_tmp_size[1] = b_trueCount;
      for (i = 0; i < b_trueCount; i++) {
        d_tmp_data[i] = (static_cast<double>(c_tmp_data[i]) - 1.0) + 1.0;
      }

      interp1(b_tmp_data, tmp_size, s_data, s_size, d_tmp_data, b_tmp_size,
              e_tmp_data, c_tmp_size);
      iyLead = 0;
      for (ixLead = 0; ixLead < 363; ixLead++) {
        if (!(b[ixLead] != 0.0)) {
          b[ixLead] = e_tmp_data[iyLead];
          iyLead++;
        }
      }
    }

    work = 0.0;
    ixLead = 0;
    indEnd = 362;
    for (iyLead = 0; iyLead < 363; iyLead++) {
      if (s[iyLead] != 0.0) {
        if (work == 0.0) {
          ixLead = iyLead;
        }

        indEnd = iyLead;
        work++;
      }
    }

    if (1 > ixLead) {
      iyLead = 0;
    } else {
      iyLead = ixLead;
    }

    for (i = 0; i < iyLead; i++) {
      b[i] = s[ixLead];
    }

    if (indEnd + 2 > 363) {
      i = -1;
      ixLead = -1;
    } else {
      i = indEnd;
      ixLead = 362;
    }

    iyLead = ixLead - i;
    for (ixLead = 0; ixLead < iyLead; ixLead++) {
      b[(i + ixLead) + 1] = s[indEnd];
    }

    std::memcpy(&s[0], &b[0], 363U * sizeof(double));
  }

  std::memset(&maxVals[0], 0, 364U * sizeof(boolean_T));
  ixLead = 1;
  iyLead = 0;
  work = s[0];
  for (indEnd = 0; indEnd < 362; indEnd++) {
    tmp2 = work;
    work = s[ixLead];
    b_y[iyLead] = s[ixLead] - tmp2;
    ixLead++;
    iyLead++;
  }

  for (i = 0; i < 362; i++) {
    maxVals[i + 1] = (b_y[i] < 0.0);
  }

  uniquePts[0] = true;
  for (ixLead = 0; ixLead < 363; ixLead++) {
    uniquePts[ixLead + 1] = (A[ixLead + 1] != A[ixLead]);
  }

  y = false;
  iyLead = 0;
  exitg1 = false;
  while ((!exitg1) && (iyLead <= 363)) {
    if (nanMask[iyLead]) {
      y = true;
      exitg1 = true;
    } else {
      iyLead++;
    }
  }

  if (y) {
    nanMask[0] = uniquePts[0];
    for (ixLead = 0; ixLead < 363; ixLead++) {
      nanMask[ixLead + 1] = (uniquePts[ixLead + 1] && ((!rtIsNaN(A[ixLead + 1]))
        || (!rtIsNaN(A[ixLead]))));
    }

    std::memcpy(&uniquePts[0], &nanMask[0], 364U * sizeof(boolean_T));
  }

  inflectionPts[0] = true;
  for (ixLead = 0; ixLead < 362; ixLead++) {
    inflectionPts[ixLead + 1] = ((s[ixLead] != s[ixLead + 1]) &&
      uniquePts[ixLead + 1]);
  }

  inflectionPts[363] = true;
}

//
// Arguments    : const int A_size[1]
//                boolean_T maxVals_data[]
//                const int maxVals_size[1]
//                const double P_data[]
// Return Type  : void
//
static void c_restrictNumberOfExtrema(const int A_size[1], boolean_T
  maxVals_data[], const int maxVals_size[1], const double P_data[])
{
  int loop_ub;
  int i;
  int trueCount;
  int partialTrueCount;
  unsigned int idx_data[365];
  int x_size[1];
  unsigned int locMaxima_data[365];
  short tmp_data[365];
  double x_data[365];
  int iidx_data[365];
  int iidx_size[1];
  if (A_size[0] >= 1) {
    loop_ub = A_size[0] - 1;
    for (i = 0; i <= loop_ub; i++) {
      idx_data[i] = static_cast<unsigned int>(i + 1);
    }
  }

  loop_ub = maxVals_size[0] - 1;
  trueCount = 0;
  partialTrueCount = 0;
  for (i = 0; i <= loop_ub; i++) {
    if (maxVals_data[i]) {
      trueCount++;
    }

    if (maxVals_data[i]) {
      tmp_data[partialTrueCount] = static_cast<short>(i + 1);
      partialTrueCount++;
    }
  }

  for (i = 0; i < trueCount; i++) {
    locMaxima_data[i] = idx_data[tmp_data[i] - 1];
  }

  x_size[0] = trueCount;
  for (i = 0; i < trueCount; i++) {
    x_data[i] = P_data[static_cast<int>(locMaxima_data[i]) - 1];
  }

  sort(x_data, x_size, iidx_data, iidx_size);
  loop_ub = iidx_size[0];
  for (i = 0; i < loop_ub; i++) {
    x_data[i] = iidx_data[i];
  }

  if (3 > iidx_size[0]) {
    i = 0;
    partialTrueCount = 0;
  } else {
    i = 2;
    partialTrueCount = iidx_size[0];
  }

  loop_ub = partialTrueCount - i;
  for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
    iidx_data[partialTrueCount] = static_cast<int>(locMaxima_data[static_cast<
      int>(x_data[i + partialTrueCount]) - 1]);
  }

  for (i = 0; i < loop_ub; i++) {
    maxVals_data[iidx_data[i] - 1] = false;
  }
}

//
// Arguments    : const double A[363]
//                boolean_T maxVals[363]
// Return Type  : void
//
static void d_adjustFlatRegions(const double A[363], boolean_T maxVals[363])
{
  int ctr;
  boolean_T y;
  int k;
  boolean_T exitg1;
  int i;
  double leftRange_data[364];
  int leftRange_size[1];
  double rightRange_data[365];
  int rightRange_size[1];
  int loop_ub;
  int i1;
  boolean_T flatRegion_data[364];
  boolean_T x_data[366];
  int result_size[2];
  double result_data[732];
  short tmp_data[364];
  int b_tmp_data[364];
  double b_x_data[366];
  int x_size[1];
  int c_tmp_data[365];
  ctr = 0;
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= 362)) {
    if (maxVals[k]) {
      y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (y) {
    ctr = 1;
  }

  i = (1 <= ctr) - 1;
  if (0 <= (1 <= ctr) - 1) {
    d_findUniqueRanges(A, leftRange_data, leftRange_size, rightRange_data,
                       rightRange_size);
    loop_ub = rightRange_size[0];
  }

  if (0 <= i) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      flatRegion_data[i1] = (rightRange_data[i1] > leftRange_data[i1]);
    }
  }

  for (k = 0; k <= i; k++) {
    y = false;
    ctr = 1;
    exitg1 = false;
    while ((!exitg1) && (ctr <= rightRange_size[0])) {
      if (!flatRegion_data[ctr - 1]) {
        ctr++;
      } else {
        y = true;
        exitg1 = true;
      }
    }

    if (y) {
      loop_ub = leftRange_size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        x_data[i1] = (maxVals[static_cast<int>(leftRange_data[i1]) - 1] &&
                      flatRegion_data[i1]);
      }

      y = false;
      ctr = 1;
      exitg1 = false;
      while ((!exitg1) && (ctr <= loop_ub)) {
        if (!x_data[ctr - 1]) {
          ctr++;
        } else {
          y = true;
          exitg1 = true;
        }
      }

      if (y) {
        int partialTrueCount;
        ctr = leftRange_size[0] - 1;
        loop_ub = 0;
        partialTrueCount = 0;
        for (int b_i = 0; b_i <= ctr; b_i++) {
          i1 = static_cast<int>(leftRange_data[b_i]) - 1;
          if (maxVals[i1] && flatRegion_data[b_i]) {
            loop_ub++;
          }

          if (maxVals[i1] && flatRegion_data[b_i]) {
            tmp_data[partialTrueCount] = static_cast<short>(b_i + 1);
            partialTrueCount++;
          }
        }

        result_size[0] = loop_ub;
        result_size[1] = 2;
        for (i1 = 0; i1 < loop_ub; i1++) {
          result_data[i1] = leftRange_data[tmp_data[i1] - 1];
        }

        for (i1 = 0; i1 < loop_ub; i1++) {
          result_data[i1 + loop_ub] = rightRange_data[tmp_data[i1] - 1];
        }

        for (i1 = 0; i1 < loop_ub; i1++) {
          b_tmp_data[i1] = static_cast<int>(result_data[i1]);
        }

        for (i1 = 0; i1 < loop_ub; i1++) {
          maxVals[b_tmp_data[i1] - 1] = false;
        }

        mean(result_data, result_size, b_x_data, x_size);
        ctr = x_size[0];
        for (loop_ub = 0; loop_ub < ctr; loop_ub++) {
          b_x_data[loop_ub] = std::floor(b_x_data[loop_ub]);
        }

        loop_ub = x_size[0];
        for (i1 = 0; i1 < loop_ub; i1++) {
          c_tmp_data[i1] = static_cast<int>(b_x_data[i1]);
        }

        for (i1 = 0; i1 < loop_ub; i1++) {
          maxVals[c_tmp_data[i1] - 1] = true;
        }
      }
    }
  }
}

//
// Arguments    : const double v[363]
//                double left_data[]
//                int left_size[1]
//                double right_data[]
//                int right_size[1]
// Return Type  : void
//
static void d_findUniqueRanges(const double v[363], double left_data[], int
  left_size[1], double right_data[], int right_size[1])
{
  int ixLead;
  int iyLead;
  double work;
  int m;
  short idxTemp[363];
  double d[362];
  ixLead = 1;
  iyLead = 0;
  work = v[0];
  for (m = 0; m < 362; m++) {
    double tmp2;
    tmp2 = work;
    work = v[ixLead];
    d[iyLead] = v[ixLead] - tmp2;
    ixLead++;
    iyLead++;
  }

  std::memset(&idxTemp[0], 0, 363U * sizeof(short));
  work = 1.0;
  for (ixLead = 0; ixLead < 362; ixLead++) {
    if (d[ixLead] != 0.0) {
      idxTemp[static_cast<int>(work) - 1] = static_cast<short>(ixLead + 1);
      work++;
    }
  }

  if (1.0 > work - 1.0) {
    ixLead = 0;
  } else {
    ixLead = static_cast<int>(work - 1.0);
  }

  left_size[0] = ixLead + 1;
  left_data[0] = 1.0;
  for (iyLead = 0; iyLead < ixLead; iyLead++) {
    left_data[iyLead + 1] = static_cast<double>(idxTemp[iyLead]) + 1.0;
  }

  if (2 > left_size[0]) {
    iyLead = 0;
    m = 0;
  } else {
    iyLead = 1;
    m = left_size[0];
  }

  ixLead = m - iyLead;
  right_size[0] = ixLead + 1;
  for (m = 0; m < ixLead; m++) {
    right_data[m] = left_data[iyLead + m] - 1.0;
  }

  right_data[ixLead] = 363.0;
}

//
// Arguments    : const double A[363]
//                boolean_T maxVals[363]
//                boolean_T inflectionPts[363]
// Return Type  : void
//
static void d_getAllLocalMax(const double A[363], boolean_T maxVals[363],
  boolean_T inflectionPts[363])
{
  int ixLead;
  int iyLead;
  double work;
  int indEnd;
  double tmp2;
  double s[362];
  boolean_T y;
  boolean_T nanMask[363];
  boolean_T exitg1;
  boolean_T x[362];
  double b[362];
  int i;
  boolean_T uniquePts[363];
  double b_y[361];
  int tmp_size[2];
  short tmp_data[362];
  int s_size[1];
  double b_tmp_data[362];
  short c_tmp_data[362];
  int b_tmp_size[2];
  double s_data[362];
  double d_tmp_data[362];
  double e_tmp_data[364];
  int c_tmp_size[2];
  ixLead = 1;
  iyLead = 0;
  work = A[0];
  for (indEnd = 0; indEnd < 362; indEnd++) {
    tmp2 = work;
    work = A[ixLead];
    s[iyLead] = A[ixLead] - tmp2;
    ixLead++;
    iyLead++;
  }

  for (iyLead = 0; iyLead < 362; iyLead++) {
    work = s[iyLead];
    if (s[iyLead] < 0.0) {
      work = -1.0;
    } else if (s[iyLead] > 0.0) {
      work = 1.0;
    } else {
      if (s[iyLead] == 0.0) {
        work = 0.0;
      }
    }

    s[iyLead] = work;
  }

  for (ixLead = 0; ixLead < 363; ixLead++) {
    nanMask[ixLead] = rtIsNaN(A[ixLead]);
  }

  y = false;
  iyLead = 0;
  exitg1 = false;
  while ((!exitg1) && (iyLead <= 362)) {
    if (nanMask[iyLead]) {
      y = true;
      exitg1 = true;
    } else {
      iyLead++;
    }
  }

  if (y) {
    for (ixLead = 0; ixLead < 362; ixLead++) {
      if (nanMask[ixLead]) {
        s[ixLead] = -1.0;
      }

      if ((!nanMask[ixLead]) && nanMask[ixLead + 1]) {
        s[ixLead] = 1.0;
      }
    }
  }

  y = true;
  iyLead = 0;
  exitg1 = false;
  while ((!exitg1) && (iyLead <= 361)) {
    if (s[iyLead] == 0.0) {
      y = false;
      exitg1 = true;
    } else {
      iyLead++;
    }
  }

  if (!y) {
    for (ixLead = 0; ixLead < 362; ixLead++) {
      b[ixLead] = s[ixLead];
      x[ixLead] = (s[ixLead] != 0.0);
    }

    ixLead = x[0];
    for (iyLead = 0; iyLead < 361; iyLead++) {
      ixLead += x[iyLead + 1];
    }

    if (ixLead > 1) {
      int trueCount;
      int b_trueCount;
      trueCount = 0;
      iyLead = 0;
      b_trueCount = 0;
      indEnd = 0;
      for (ixLead = 0; ixLead < 362; ixLead++) {
        if (s[ixLead] != 0.0) {
          trueCount++;
          tmp_data[iyLead] = static_cast<short>(ixLead + 1);
          iyLead++;
        }

        if (!(s[ixLead] != 0.0)) {
          b_trueCount++;
          c_tmp_data[indEnd] = static_cast<short>(ixLead + 1);
          indEnd++;
        }
      }

      tmp_size[0] = 1;
      tmp_size[1] = trueCount;
      for (i = 0; i < trueCount; i++) {
        b_tmp_data[i] = (static_cast<double>(tmp_data[i]) - 1.0) + 1.0;
      }

      s_size[0] = trueCount;
      for (i = 0; i < trueCount; i++) {
        s_data[i] = s[tmp_data[i] - 1];
      }

      b_tmp_size[0] = 1;
      b_tmp_size[1] = b_trueCount;
      for (i = 0; i < b_trueCount; i++) {
        d_tmp_data[i] = (static_cast<double>(c_tmp_data[i]) - 1.0) + 1.0;
      }

      interp1(b_tmp_data, tmp_size, s_data, s_size, d_tmp_data, b_tmp_size,
              e_tmp_data, c_tmp_size);
      iyLead = 0;
      for (ixLead = 0; ixLead < 362; ixLead++) {
        if (!(b[ixLead] != 0.0)) {
          b[ixLead] = e_tmp_data[iyLead];
          iyLead++;
        }
      }
    }

    work = 0.0;
    ixLead = 0;
    indEnd = 361;
    for (iyLead = 0; iyLead < 362; iyLead++) {
      if (s[iyLead] != 0.0) {
        if (work == 0.0) {
          ixLead = iyLead;
        }

        indEnd = iyLead;
        work++;
      }
    }

    if (1 > ixLead) {
      iyLead = 0;
    } else {
      iyLead = ixLead;
    }

    for (i = 0; i < iyLead; i++) {
      b[i] = s[ixLead];
    }

    if (indEnd + 2 > 362) {
      i = -1;
      ixLead = -1;
    } else {
      i = indEnd;
      ixLead = 361;
    }

    iyLead = ixLead - i;
    for (ixLead = 0; ixLead < iyLead; ixLead++) {
      b[(i + ixLead) + 1] = s[indEnd];
    }

    std::memcpy(&s[0], &b[0], 362U * sizeof(double));
  }

  std::memset(&maxVals[0], 0, 363U * sizeof(boolean_T));
  ixLead = 1;
  iyLead = 0;
  work = s[0];
  for (indEnd = 0; indEnd < 361; indEnd++) {
    tmp2 = work;
    work = s[ixLead];
    b_y[iyLead] = s[ixLead] - tmp2;
    ixLead++;
    iyLead++;
  }

  for (i = 0; i < 361; i++) {
    maxVals[i + 1] = (b_y[i] < 0.0);
  }

  uniquePts[0] = true;
  for (ixLead = 0; ixLead < 362; ixLead++) {
    uniquePts[ixLead + 1] = (A[ixLead + 1] != A[ixLead]);
  }

  y = false;
  iyLead = 0;
  exitg1 = false;
  while ((!exitg1) && (iyLead <= 362)) {
    if (nanMask[iyLead]) {
      y = true;
      exitg1 = true;
    } else {
      iyLead++;
    }
  }

  if (y) {
    nanMask[0] = uniquePts[0];
    for (ixLead = 0; ixLead < 362; ixLead++) {
      nanMask[ixLead + 1] = (uniquePts[ixLead + 1] && ((!rtIsNaN(A[ixLead + 1]))
        || (!rtIsNaN(A[ixLead]))));
    }

    std::memcpy(&uniquePts[0], &nanMask[0], 363U * sizeof(boolean_T));
  }

  inflectionPts[0] = true;
  for (ixLead = 0; ixLead < 361; ixLead++) {
    inflectionPts[ixLead + 1] = ((s[ixLead] != s[ixLead + 1]) &&
      uniquePts[ixLead + 1]);
  }

  inflectionPts[362] = true;
}

//
// Arguments    : boolean_T maxVals[364]
//                const double P[364]
// Return Type  : void
//
static void d_restrictNumberOfExtrema(boolean_T maxVals[364], const double P[364])
{
  int trueCount;
  int partialTrueCount;
  int i;
  short locMaxima_data[364];
  short tmp_data[364];
  int x_size[1];
  double x_data[365];
  int iidx_data[365];
  int iidx_size[1];
  trueCount = 0;
  partialTrueCount = 0;
  for (i = 0; i < 364; i++) {
    if (maxVals[i]) {
      trueCount++;
    }

    if (maxVals[i]) {
      tmp_data[partialTrueCount] = static_cast<short>(i + 1);
      partialTrueCount++;
    }
  }

  if (0 <= trueCount - 1) {
    std::memcpy(&locMaxima_data[0], &tmp_data[0], trueCount * sizeof(short));
  }

  x_size[0] = trueCount;
  for (i = 0; i < trueCount; i++) {
    x_data[i] = P[locMaxima_data[i] - 1];
  }

  sort(x_data, x_size, iidx_data, iidx_size);
  partialTrueCount = iidx_size[0];
  for (i = 0; i < partialTrueCount; i++) {
    x_data[i] = iidx_data[i];
  }

  if (3 > iidx_size[0]) {
    i = 0;
    trueCount = 0;
  } else {
    i = 2;
    trueCount = iidx_size[0];
  }

  partialTrueCount = trueCount - i;
  for (trueCount = 0; trueCount < partialTrueCount; trueCount++) {
    iidx_data[trueCount] = locMaxima_data[static_cast<int>(x_data[i + trueCount])
      - 1];
  }

  for (i = 0; i < partialTrueCount; i++) {
    maxVals[iidx_data[i] - 1] = false;
  }
}

//
// Arguments    : const double A[362]
//                boolean_T maxVals[362]
// Return Type  : void
//
static void e_adjustFlatRegions(const double A[362], boolean_T maxVals[362])
{
  int ctr;
  boolean_T y;
  int k;
  boolean_T exitg1;
  int i;
  double leftRange_data[363];
  int leftRange_size[1];
  double rightRange_data[364];
  int rightRange_size[1];
  int loop_ub;
  int i1;
  boolean_T flatRegion_data[363];
  boolean_T x_data[366];
  int result_size[2];
  double result_data[732];
  short tmp_data[363];
  int b_tmp_data[363];
  double b_x_data[366];
  int x_size[1];
  int c_tmp_data[365];
  ctr = 0;
  y = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= 361)) {
    if (maxVals[k]) {
      y = true;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (y) {
    ctr = 1;
  }

  i = (1 <= ctr) - 1;
  if (0 <= (1 <= ctr) - 1) {
    e_findUniqueRanges(A, leftRange_data, leftRange_size, rightRange_data,
                       rightRange_size);
    loop_ub = rightRange_size[0];
  }

  if (0 <= i) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      flatRegion_data[i1] = (rightRange_data[i1] > leftRange_data[i1]);
    }
  }

  for (k = 0; k <= i; k++) {
    y = false;
    ctr = 1;
    exitg1 = false;
    while ((!exitg1) && (ctr <= rightRange_size[0])) {
      if (!flatRegion_data[ctr - 1]) {
        ctr++;
      } else {
        y = true;
        exitg1 = true;
      }
    }

    if (y) {
      loop_ub = leftRange_size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        x_data[i1] = (maxVals[static_cast<int>(leftRange_data[i1]) - 1] &&
                      flatRegion_data[i1]);
      }

      y = false;
      ctr = 1;
      exitg1 = false;
      while ((!exitg1) && (ctr <= loop_ub)) {
        if (!x_data[ctr - 1]) {
          ctr++;
        } else {
          y = true;
          exitg1 = true;
        }
      }

      if (y) {
        int partialTrueCount;
        ctr = leftRange_size[0] - 1;
        loop_ub = 0;
        partialTrueCount = 0;
        for (int b_i = 0; b_i <= ctr; b_i++) {
          i1 = static_cast<int>(leftRange_data[b_i]) - 1;
          if (maxVals[i1] && flatRegion_data[b_i]) {
            loop_ub++;
          }

          if (maxVals[i1] && flatRegion_data[b_i]) {
            tmp_data[partialTrueCount] = static_cast<short>(b_i + 1);
            partialTrueCount++;
          }
        }

        result_size[0] = loop_ub;
        result_size[1] = 2;
        for (i1 = 0; i1 < loop_ub; i1++) {
          result_data[i1] = leftRange_data[tmp_data[i1] - 1];
        }

        for (i1 = 0; i1 < loop_ub; i1++) {
          result_data[i1 + loop_ub] = rightRange_data[tmp_data[i1] - 1];
        }

        for (i1 = 0; i1 < loop_ub; i1++) {
          b_tmp_data[i1] = static_cast<int>(result_data[i1]);
        }

        for (i1 = 0; i1 < loop_ub; i1++) {
          maxVals[b_tmp_data[i1] - 1] = false;
        }

        mean(result_data, result_size, b_x_data, x_size);
        ctr = x_size[0];
        for (loop_ub = 0; loop_ub < ctr; loop_ub++) {
          b_x_data[loop_ub] = std::floor(b_x_data[loop_ub]);
        }

        loop_ub = x_size[0];
        for (i1 = 0; i1 < loop_ub; i1++) {
          c_tmp_data[i1] = static_cast<int>(b_x_data[i1]);
        }

        for (i1 = 0; i1 < loop_ub; i1++) {
          maxVals[c_tmp_data[i1] - 1] = true;
        }
      }
    }
  }
}

//
// Arguments    : const double v[362]
//                double left_data[]
//                int left_size[1]
//                double right_data[]
//                int right_size[1]
// Return Type  : void
//
static void e_findUniqueRanges(const double v[362], double left_data[], int
  left_size[1], double right_data[], int right_size[1])
{
  int ixLead;
  int iyLead;
  double work;
  int m;
  short idxTemp[362];
  double d[361];
  ixLead = 1;
  iyLead = 0;
  work = v[0];
  for (m = 0; m < 361; m++) {
    double tmp2;
    tmp2 = work;
    work = v[ixLead];
    d[iyLead] = v[ixLead] - tmp2;
    ixLead++;
    iyLead++;
  }

  std::memset(&idxTemp[0], 0, 362U * sizeof(short));
  work = 1.0;
  for (ixLead = 0; ixLead < 361; ixLead++) {
    if (d[ixLead] != 0.0) {
      idxTemp[static_cast<int>(work) - 1] = static_cast<short>(ixLead + 1);
      work++;
    }
  }

  if (1.0 > work - 1.0) {
    ixLead = 0;
  } else {
    ixLead = static_cast<int>(work - 1.0);
  }

  left_size[0] = ixLead + 1;
  left_data[0] = 1.0;
  for (iyLead = 0; iyLead < ixLead; iyLead++) {
    left_data[iyLead + 1] = static_cast<double>(idxTemp[iyLead]) + 1.0;
  }

  if (2 > left_size[0]) {
    iyLead = 0;
    m = 0;
  } else {
    iyLead = 1;
    m = left_size[0];
  }

  ixLead = m - iyLead;
  right_size[0] = ixLead + 1;
  for (m = 0; m < ixLead; m++) {
    right_data[m] = left_data[iyLead + m] - 1.0;
  }

  right_data[ixLead] = 362.0;
}

//
// Arguments    : const double A[362]
//                boolean_T maxVals[362]
//                boolean_T inflectionPts[362]
// Return Type  : void
//
static void e_getAllLocalMax(const double A[362], boolean_T maxVals[362],
  boolean_T inflectionPts[362])
{
  int ixLead;
  int iyLead;
  double work;
  int indEnd;
  double tmp2;
  double s[361];
  boolean_T y;
  boolean_T nanMask[362];
  boolean_T exitg1;
  boolean_T x[361];
  double b[361];
  int i;
  boolean_T uniquePts[362];
  double b_y[360];
  int tmp_size[2];
  short tmp_data[361];
  int s_size[1];
  double b_tmp_data[361];
  short c_tmp_data[361];
  int b_tmp_size[2];
  double s_data[361];
  double d_tmp_data[361];
  double e_tmp_data[364];
  int c_tmp_size[2];
  ixLead = 1;
  iyLead = 0;
  work = A[0];
  for (indEnd = 0; indEnd < 361; indEnd++) {
    tmp2 = work;
    work = A[ixLead];
    s[iyLead] = A[ixLead] - tmp2;
    ixLead++;
    iyLead++;
  }

  for (iyLead = 0; iyLead < 361; iyLead++) {
    work = s[iyLead];
    if (s[iyLead] < 0.0) {
      work = -1.0;
    } else if (s[iyLead] > 0.0) {
      work = 1.0;
    } else {
      if (s[iyLead] == 0.0) {
        work = 0.0;
      }
    }

    s[iyLead] = work;
  }

  for (ixLead = 0; ixLead < 362; ixLead++) {
    nanMask[ixLead] = rtIsNaN(A[ixLead]);
  }

  y = false;
  iyLead = 0;
  exitg1 = false;
  while ((!exitg1) && (iyLead <= 361)) {
    if (nanMask[iyLead]) {
      y = true;
      exitg1 = true;
    } else {
      iyLead++;
    }
  }

  if (y) {
    for (ixLead = 0; ixLead < 361; ixLead++) {
      if (nanMask[ixLead]) {
        s[ixLead] = -1.0;
      }

      if ((!nanMask[ixLead]) && nanMask[ixLead + 1]) {
        s[ixLead] = 1.0;
      }
    }
  }

  y = true;
  iyLead = 0;
  exitg1 = false;
  while ((!exitg1) && (iyLead <= 360)) {
    if (s[iyLead] == 0.0) {
      y = false;
      exitg1 = true;
    } else {
      iyLead++;
    }
  }

  if (!y) {
    for (ixLead = 0; ixLead < 361; ixLead++) {
      b[ixLead] = s[ixLead];
      x[ixLead] = (s[ixLead] != 0.0);
    }

    ixLead = x[0];
    for (iyLead = 0; iyLead < 360; iyLead++) {
      ixLead += x[iyLead + 1];
    }

    if (ixLead > 1) {
      int trueCount;
      int b_trueCount;
      trueCount = 0;
      iyLead = 0;
      b_trueCount = 0;
      indEnd = 0;
      for (ixLead = 0; ixLead < 361; ixLead++) {
        if (s[ixLead] != 0.0) {
          trueCount++;
          tmp_data[iyLead] = static_cast<short>(ixLead + 1);
          iyLead++;
        }

        if (!(s[ixLead] != 0.0)) {
          b_trueCount++;
          c_tmp_data[indEnd] = static_cast<short>(ixLead + 1);
          indEnd++;
        }
      }

      tmp_size[0] = 1;
      tmp_size[1] = trueCount;
      for (i = 0; i < trueCount; i++) {
        b_tmp_data[i] = (static_cast<double>(tmp_data[i]) - 1.0) + 1.0;
      }

      s_size[0] = trueCount;
      for (i = 0; i < trueCount; i++) {
        s_data[i] = s[tmp_data[i] - 1];
      }

      b_tmp_size[0] = 1;
      b_tmp_size[1] = b_trueCount;
      for (i = 0; i < b_trueCount; i++) {
        d_tmp_data[i] = (static_cast<double>(c_tmp_data[i]) - 1.0) + 1.0;
      }

      interp1(b_tmp_data, tmp_size, s_data, s_size, d_tmp_data, b_tmp_size,
              e_tmp_data, c_tmp_size);
      iyLead = 0;
      for (ixLead = 0; ixLead < 361; ixLead++) {
        if (!(b[ixLead] != 0.0)) {
          b[ixLead] = e_tmp_data[iyLead];
          iyLead++;
        }
      }
    }

    work = 0.0;
    ixLead = 0;
    indEnd = 360;
    for (iyLead = 0; iyLead < 361; iyLead++) {
      if (s[iyLead] != 0.0) {
        if (work == 0.0) {
          ixLead = iyLead;
        }

        indEnd = iyLead;
        work++;
      }
    }

    if (1 > ixLead) {
      iyLead = 0;
    } else {
      iyLead = ixLead;
    }

    for (i = 0; i < iyLead; i++) {
      b[i] = s[ixLead];
    }

    if (indEnd + 2 > 361) {
      i = -1;
      ixLead = -1;
    } else {
      i = indEnd;
      ixLead = 360;
    }

    iyLead = ixLead - i;
    for (ixLead = 0; ixLead < iyLead; ixLead++) {
      b[(i + ixLead) + 1] = s[indEnd];
    }

    std::memcpy(&s[0], &b[0], 361U * sizeof(double));
  }

  std::memset(&maxVals[0], 0, 362U * sizeof(boolean_T));
  ixLead = 1;
  iyLead = 0;
  work = s[0];
  for (indEnd = 0; indEnd < 360; indEnd++) {
    tmp2 = work;
    work = s[ixLead];
    b_y[iyLead] = s[ixLead] - tmp2;
    ixLead++;
    iyLead++;
  }

  for (i = 0; i < 360; i++) {
    maxVals[i + 1] = (b_y[i] < 0.0);
  }

  uniquePts[0] = true;
  for (ixLead = 0; ixLead < 361; ixLead++) {
    uniquePts[ixLead + 1] = (A[ixLead + 1] != A[ixLead]);
  }

  y = false;
  iyLead = 0;
  exitg1 = false;
  while ((!exitg1) && (iyLead <= 361)) {
    if (nanMask[iyLead]) {
      y = true;
      exitg1 = true;
    } else {
      iyLead++;
    }
  }

  if (y) {
    nanMask[0] = uniquePts[0];
    for (ixLead = 0; ixLead < 361; ixLead++) {
      nanMask[ixLead + 1] = (uniquePts[ixLead + 1] && ((!rtIsNaN(A[ixLead + 1]))
        || (!rtIsNaN(A[ixLead]))));
    }

    std::memcpy(&uniquePts[0], &nanMask[0], 362U * sizeof(boolean_T));
  }

  inflectionPts[0] = true;
  for (ixLead = 0; ixLead < 360; ixLead++) {
    inflectionPts[ixLead + 1] = ((s[ixLead] != s[ixLead + 1]) &&
      uniquePts[ixLead + 1]);
  }

  inflectionPts[361] = true;
}

//
// Arguments    : boolean_T maxVals[363]
//                const double P[363]
// Return Type  : void
//
static void e_restrictNumberOfExtrema(boolean_T maxVals[363], const double P[363])
{
  int trueCount;
  int partialTrueCount;
  int i;
  short locMaxima_data[363];
  short tmp_data[363];
  int x_size[1];
  double x_data[365];
  int iidx_data[365];
  int iidx_size[1];
  trueCount = 0;
  partialTrueCount = 0;
  for (i = 0; i < 363; i++) {
    if (maxVals[i]) {
      trueCount++;
    }

    if (maxVals[i]) {
      tmp_data[partialTrueCount] = static_cast<short>(i + 1);
      partialTrueCount++;
    }
  }

  if (0 <= trueCount - 1) {
    std::memcpy(&locMaxima_data[0], &tmp_data[0], trueCount * sizeof(short));
  }

  x_size[0] = trueCount;
  for (i = 0; i < trueCount; i++) {
    x_data[i] = P[locMaxima_data[i] - 1];
  }

  sort(x_data, x_size, iidx_data, iidx_size);
  partialTrueCount = iidx_size[0];
  for (i = 0; i < partialTrueCount; i++) {
    x_data[i] = iidx_data[i];
  }

  if (3 > iidx_size[0]) {
    i = 0;
    trueCount = 0;
  } else {
    i = 2;
    trueCount = iidx_size[0];
  }

  partialTrueCount = trueCount - i;
  for (trueCount = 0; trueCount < partialTrueCount; trueCount++) {
    iidx_data[trueCount] = locMaxima_data[static_cast<int>(x_data[i + trueCount])
      - 1];
  }

  for (i = 0; i < partialTrueCount; i++) {
    maxVals[iidx_data[i] - 1] = false;
  }
}

//
// Arguments    : boolean_T maxVals[362]
//                const double P[362]
// Return Type  : void
//
static void f_restrictNumberOfExtrema(boolean_T maxVals[362], const double P[362])
{
  int trueCount;
  int partialTrueCount;
  int i;
  short locMaxima_data[362];
  short tmp_data[362];
  int x_size[1];
  double x_data[365];
  int iidx_data[365];
  int iidx_size[1];
  trueCount = 0;
  partialTrueCount = 0;
  for (i = 0; i < 362; i++) {
    if (maxVals[i]) {
      trueCount++;
    }

    if (maxVals[i]) {
      tmp_data[partialTrueCount] = static_cast<short>(i + 1);
      partialTrueCount++;
    }
  }

  if (0 <= trueCount - 1) {
    std::memcpy(&locMaxima_data[0], &tmp_data[0], trueCount * sizeof(short));
  }

  x_size[0] = trueCount;
  for (i = 0; i < trueCount; i++) {
    x_data[i] = P[locMaxima_data[i] - 1];
  }

  sort(x_data, x_size, iidx_data, iidx_size);
  partialTrueCount = iidx_size[0];
  for (i = 0; i < partialTrueCount; i++) {
    x_data[i] = iidx_data[i];
  }

  if (3 > iidx_size[0]) {
    i = 0;
    trueCount = 0;
  } else {
    i = 2;
    trueCount = iidx_size[0];
  }

  partialTrueCount = trueCount - i;
  for (trueCount = 0; trueCount < partialTrueCount; trueCount++) {
    iidx_data[trueCount] = locMaxima_data[static_cast<int>(x_data[i + trueCount])
      - 1];
  }

  for (i = 0; i < partialTrueCount; i++) {
    maxVals[iidx_data[i] - 1] = false;
  }
}

//
// Arguments    : const double A_data[]
//                const int A_size[1]
//                const double P_data[]
//                boolean_T maxVals_data[]
//                const int maxVals_size[1]
//                const double x_data[]
// Return Type  : void
//
static void filterByDistance(const double A_data[], const int A_size[1], const
  double P_data[], boolean_T maxVals_data[], const int maxVals_size[1], const
  double x_data[])
{
  int loop_ub;
  int i;
  int trueCount;
  int idx;
  unsigned int idx_data[365];
  int b_i;
  unsigned int locMaxima_data[365];
  short tmp_data[365];
  double leftIndices_data[365];
  double rightIndices_data[365];
  double left;
  int k;
  int right;
  int leftIdx_size[2];
  double leftIdx_data[364];
  int b_maxVals_size[1];
  boolean_T b_maxVals_data[364];
  if (A_size[0] >= 1) {
    loop_ub = A_size[0] - 1;
    for (i = 0; i <= loop_ub; i++) {
      idx_data[i] = static_cast<unsigned int>(i + 1);
    }
  }

  loop_ub = maxVals_size[0] - 1;
  trueCount = 0;
  idx = 0;
  for (b_i = 0; b_i <= loop_ub; b_i++) {
    if (maxVals_data[b_i]) {
      trueCount++;
    }

    if (maxVals_data[b_i]) {
      tmp_data[idx] = static_cast<short>(b_i + 1);
      idx++;
    }
  }

  for (i = 0; i < trueCount; i++) {
    locMaxima_data[i] = idx_data[tmp_data[i] - 1];
  }

  for (i = 0; i < trueCount; i++) {
    leftIndices_data[i] = x_data[static_cast<int>(locMaxima_data[i]) - 1];
  }

  if (0 <= trueCount - 1) {
    std::memcpy(&rightIndices_data[0], &leftIndices_data[0], trueCount * sizeof
                (double));
  }

  for (b_i = 0; b_i < trueCount; b_i++) {
    k = static_cast<int>(idx_data[tmp_data[b_i] - 1]);
    i = k - 1;
    if ((!rtIsInf(A_data[i])) && (!rtIsNaN(A_data[i]))) {
      while ((k < static_cast<double>(A_size[0]) - 1.0) && (A_data[k] ==
              A_data[k - 1])) {
        k++;
      }

      rightIndices_data[b_i] = x_data[k - 1];
    }
  }

  left = 1.0;
  right = 1;
  for (b_i = 0; b_i < trueCount; b_i++) {
    int exitg1;
    int i1;
    do {
      exitg1 = 0;
      i = static_cast<int>(left) - 1;
      if (leftIndices_data[b_i] - rightIndices_data[i] >= 60.0) {
        left++;
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);

    if (static_cast<double>(b_i) + 1.0 > right) {
      right = b_i + 1;
    }

    while ((right <= static_cast<double>(trueCount) - 1.0) &&
           (leftIndices_data[right] - rightIndices_data[b_i] < 60.0)) {
      right++;
    }

    i1 = static_cast<int>(idx_data[tmp_data[b_i] - 1]) - 1;
    if ((!rtIsInf(A_data[i1])) && (!rtIsNaN(A_data[i1]))) {
      int i2;
      int i3;
      if (left > (static_cast<double>(b_i) + 1.0) - 1.0) {
        i = 0;
        i2 = 0;
        i3 = 0;
        idx = 0;
      } else {
        i2 = b_i;
        i3 = i;
        idx = b_i;
      }

      leftIdx_size[0] = 1;
      loop_ub = i2 - i;
      leftIdx_size[1] = loop_ub;
      for (i2 = 0; i2 < loop_ub; i2++) {
        leftIdx_data[i2] = locMaxima_data[i + i2];
      }

      loop_ub = idx - i3;
      b_maxVals_size[0] = loop_ub;
      for (i = 0; i < loop_ub; i++) {
        b_maxVals_data[i] = !maxVals_data[static_cast<int>(locMaxima_data[i3 + i])
          - 1];
      }

      nullAssignment(leftIdx_data, leftIdx_size, b_maxVals_data, b_maxVals_size);
      i = leftIdx_size[1];
      if (leftIdx_size[1] != 0) {
        double rightMax;
        if (leftIdx_size[1] <= 2) {
          if (leftIdx_size[1] == 1) {
            rightMax = P_data[static_cast<int>(leftIdx_data[0]) - 1];
          } else {
            i = static_cast<int>(leftIdx_data[0]) - 1;
            i2 = static_cast<int>(leftIdx_data[1]) - 1;
            if ((P_data[i] < P_data[i2]) || (rtIsNaN(P_data[i]) && (!rtIsNaN
                  (P_data[i2])))) {
              rightMax = P_data[i2];
            } else {
              rightMax = P_data[i];
            }
          }
        } else {
          i2 = static_cast<int>(leftIdx_data[0]) - 1;
          if (!rtIsNaN(P_data[i2])) {
            idx = 1;
          } else {
            boolean_T exitg2;
            idx = 0;
            k = 2;
            exitg2 = false;
            while ((!exitg2) && (k <= leftIdx_size[1])) {
              if (!rtIsNaN(P_data[static_cast<int>(leftIdx_data[k - 1]) - 1])) {
                idx = k;
                exitg2 = true;
              } else {
                k++;
              }
            }
          }

          if (idx == 0) {
            rightMax = P_data[i2];
          } else {
            rightMax = P_data[static_cast<int>(leftIdx_data[idx - 1]) - 1];
            i2 = idx + 1;
            for (k = i2; k <= i; k++) {
              i3 = static_cast<int>(leftIdx_data[k - 1]) - 1;
              if (rightMax < P_data[i3]) {
                rightMax = P_data[i3];
              }
            }
          }
        }

        if (rightMax >= P_data[i1]) {
          maxVals_data[i1] = false;
        }
      } else {
        if ((static_cast<double>(b_i) + 1.0) + 1.0 > right) {
          i = -1;
          i2 = 0;
        } else {
          i = b_i;
          i2 = right;
        }

        if (static_cast<short>((i2 - i) - 1) != 0) {
          double rightMax;
          if ((static_cast<double>(b_i) + 1.0) + 1.0 > right) {
            i = -1;
            i2 = -1;
          } else {
            i = b_i;
            i2 = right - 1;
          }

          loop_ub = i2 - i;
          if (loop_ub <= 2) {
            if (loop_ub == 1) {
              rightMax = P_data[static_cast<int>(locMaxima_data[i + 1]) - 1];
            } else {
              i2 = static_cast<int>(locMaxima_data[i + 1]) - 1;
              i = static_cast<int>(locMaxima_data[i + 2]) - 1;
              if ((P_data[i2] < P_data[i]) || (rtIsNaN(P_data[i2]) && (!rtIsNaN
                    (P_data[i])))) {
                rightMax = P_data[i];
              } else {
                rightMax = P_data[i2];
              }
            }
          } else {
            i2 = static_cast<int>(locMaxima_data[i + 1]) - 1;
            if (!rtIsNaN(P_data[i2])) {
              idx = 1;
            } else {
              boolean_T exitg2;
              idx = 0;
              k = 2;
              exitg2 = false;
              while ((!exitg2) && (k <= loop_ub)) {
                if (!rtIsNaN(P_data[static_cast<int>(locMaxima_data[i + k]) - 1]))
                {
                  idx = k;
                  exitg2 = true;
                } else {
                  k++;
                }
              }
            }

            if (idx == 0) {
              rightMax = P_data[i2];
            } else {
              rightMax = P_data[static_cast<int>(locMaxima_data[i + idx]) - 1];
              i2 = idx + 1;
              for (k = i2; k <= loop_ub; k++) {
                i3 = static_cast<int>(locMaxima_data[i + k]) - 1;
                if (rightMax < P_data[i3]) {
                  rightMax = P_data[i3];
                }
              }
            }
          }

          if (rightMax > P_data[i1]) {
            maxVals_data[i1] = false;
          }
        }
      }
    }
  }
}

//
// Arguments    : const double A_data[]
//                const int A_size[1]
//                boolean_T maxVals_data[]
//                const int maxVals_size[1]
//                double P_data[]
//                const boolean_T inflectionPts_data[]
// Return Type  : void
//
static void filterByProminence(const double A_data[], const int A_size[1],
  boolean_T maxVals_data[], const int maxVals_size[1], double P_data[], const
  boolean_T inflectionPts_data[])
{
  int idx_size_idx_1;
  int left;
  int i;
  int trueCount;
  unsigned int idx_data[365];
  int right;
  int b_i;
  boolean_T isLocMax_data[365];
  short tmp_data[365];
  if (A_size[0] < 1) {
    idx_size_idx_1 = 0;
  } else {
    idx_size_idx_1 = A_size[0];
    left = A_size[0] - 1;
    for (i = 0; i <= left; i++) {
      idx_data[i] = static_cast<unsigned int>(i + 1);
    }
  }

  left = maxVals_size[0] - 1;
  trueCount = 0;
  right = 0;
  for (b_i = 0; b_i <= left; b_i++) {
    if (maxVals_data[b_i] || inflectionPts_data[b_i]) {
      trueCount++;
    }

    if (maxVals_data[b_i] || inflectionPts_data[b_i]) {
      tmp_data[right] = static_cast<short>(b_i + 1);
      right++;
    }
  }

  for (i = 0; i < idx_size_idx_1; i++) {
    isLocMax_data[i] = maxVals_data[static_cast<int>(idx_data[i]) - 1];
  }

  for (b_i = 0; b_i < trueCount; b_i++) {
    i = static_cast<int>(idx_data[tmp_data[b_i] - 1]) - 1;
    if (isLocMax_data[i]) {
      double localMaxValue;
      localMaxValue = A_data[i];
      if (rtIsInf(A_data[i]) || rtIsNaN(A_data[i])) {
        P_data[i] = rtInf;
      } else {
        double localMins_idx_0;
        double localMins_idx_1;
        localMins_idx_0 = A_data[i];
        localMins_idx_1 = A_data[i];
        left = b_i - 1;
        right = b_i + 1;
        int exitg3;
        do {
          exitg3 = 0;
          if (left + 1 > 0) {
            idx_size_idx_1 = static_cast<int>(idx_data[tmp_data[left] - 1]) - 1;
            if (!isLocMax_data[idx_size_idx_1]) {
              if ((!(localMins_idx_0 < A_data[idx_size_idx_1])) && (!rtIsNaN
                   (A_data[idx_size_idx_1]))) {
                localMins_idx_0 = A_data[idx_size_idx_1];
              }

              left--;
            } else if (A_data[idx_size_idx_1] > localMaxValue) {
              exitg3 = 1;
            } else {
              left--;
            }
          } else {
            exitg3 = 2;
          }
        } while (exitg3 == 0);

        int exitg2;
        do {
          exitg2 = 0;
          if (right + 1 <= trueCount) {
            idx_size_idx_1 = static_cast<int>(idx_data[tmp_data[right] - 1]) - 1;
            if (!isLocMax_data[idx_size_idx_1]) {
              if ((!(localMins_idx_1 < A_data[idx_size_idx_1])) && (!rtIsNaN
                   (A_data[idx_size_idx_1]))) {
                localMins_idx_1 = A_data[idx_size_idx_1];
              }

              right++;
            } else if (A_data[idx_size_idx_1] > localMaxValue) {
              exitg2 = 1;
            } else {
              right++;
            }
          } else {
            exitg2 = 1;
          }
        } while (exitg2 == 0);

        if ((localMins_idx_0 < localMins_idx_1) || (rtIsNaN(localMins_idx_0) &&
             (!rtIsNaN(localMins_idx_1)))) {
          localMins_idx_0 = localMins_idx_1;
        }

        P_data[i] = A_data[i] - localMins_idx_0;
        maxVals_data[i] = (P_data[i] >= 0.02);
      }
    }
  }
}

//
// Arguments    : const double v_data[]
//                const int v_size[1]
//                double left_data[]
//                int left_size[1]
//                double right_data[]
//                int right_size[1]
// Return Type  : void
//
static void findUniqueRanges(const double v_data[], const int v_size[1], double
  left_data[], int left_size[1], double right_data[], int right_size[1])
{
  double tmp_data[364];
  int tmp_size[1];
  int locUniLeadMax_size_idx_0;
  int loop_ub;
  int i;
  boolean_T locUniLeadMax_data[364];
  short idxTemp_data[365];
  double ctr;
  diff(v_data, v_size, tmp_data, tmp_size);
  locUniLeadMax_size_idx_0 = tmp_size[0];
  loop_ub = tmp_size[0];
  for (i = 0; i < loop_ub; i++) {
    locUniLeadMax_data[i] = (tmp_data[i] != 0.0);
  }

  loop_ub = v_size[0];
  if (0 <= loop_ub - 1) {
    std::memset(&idxTemp_data[0], 0, loop_ub * sizeof(short));
  }

  ctr = 1.0;
  for (loop_ub = 0; loop_ub < locUniLeadMax_size_idx_0; loop_ub++) {
    if (locUniLeadMax_data[loop_ub]) {
      idxTemp_data[static_cast<int>(ctr) - 1] = static_cast<short>(loop_ub + 1);
      ctr++;
    }
  }

  if (1.0 > ctr - 1.0) {
    loop_ub = 0;
  } else {
    loop_ub = static_cast<int>(ctr - 1.0);
  }

  left_size[0] = loop_ub + 1;
  left_data[0] = 1.0;
  for (i = 0; i < loop_ub; i++) {
    left_data[i + 1] = static_cast<double>(idxTemp_data[i]) + 1.0;
  }

  if (2 > left_size[0]) {
    i = 0;
    locUniLeadMax_size_idx_0 = 0;
  } else {
    i = 1;
    locUniLeadMax_size_idx_0 = left_size[0];
  }

  loop_ub = locUniLeadMax_size_idx_0 - i;
  right_size[0] = loop_ub + 1;
  for (locUniLeadMax_size_idx_0 = 0; locUniLeadMax_size_idx_0 < loop_ub;
       locUniLeadMax_size_idx_0++) {
    right_data[locUniLeadMax_size_idx_0] = left_data[i +
      locUniLeadMax_size_idx_0] - 1.0;
  }

  right_data[loop_ub] = v_size[0];
}

//
// Arguments    : boolean_T maxVals[365]
//                const double P[365]
// Return Type  : void
//
static void g_restrictNumberOfExtrema(boolean_T maxVals[365], const double P[365])
{
  int trueCount;
  int partialTrueCount;
  int i;
  short locMaxima_data[365];
  short tmp_data[365];
  int x_size[1];
  double x_data[365];
  int iidx_data[365];
  int iidx_size[1];
  trueCount = 0;
  partialTrueCount = 0;
  for (i = 0; i < 365; i++) {
    if (maxVals[i]) {
      trueCount++;
    }

    if (maxVals[i]) {
      tmp_data[partialTrueCount] = static_cast<short>(i + 1);
      partialTrueCount++;
    }
  }

  if (0 <= trueCount - 1) {
    std::memcpy(&locMaxima_data[0], &tmp_data[0], trueCount * sizeof(short));
  }

  x_size[0] = trueCount;
  for (i = 0; i < trueCount; i++) {
    x_data[i] = P[locMaxima_data[i] - 1];
  }

  sort(x_data, x_size, iidx_data, iidx_size);
  partialTrueCount = iidx_size[0];
  for (i = 0; i < partialTrueCount; i++) {
    x_data[i] = iidx_data[i];
  }

  if (3 > iidx_size[0]) {
    i = 0;
    trueCount = 0;
  } else {
    i = 2;
    trueCount = iidx_size[0];
  }

  partialTrueCount = trueCount - i;
  for (trueCount = 0; trueCount < partialTrueCount; trueCount++) {
    iidx_data[trueCount] = locMaxima_data[static_cast<int>(x_data[i + trueCount])
      - 1];
  }

  for (i = 0; i < partialTrueCount; i++) {
    maxVals[iidx_data[i] - 1] = false;
  }
}

//
// Arguments    : const double A_data[]
//                const int A_size[1]
//                boolean_T maxVals_data[]
//                int maxVals_size[1]
//                boolean_T inflectionPts_data[]
//                int inflectionPts_size[1]
// Return Type  : void
//
static void getAllLocalMax(const double A_data[], const int A_size[1], boolean_T
  maxVals_data[], int maxVals_size[1], boolean_T inflectionPts_data[], int
  inflectionPts_size[1])
{
  double s_data[364];
  int s_size[1];
  int nx;
  int k;
  int indEnd;
  double ctr;
  int loop_ub;
  int i;
  boolean_T y;
  boolean_T nanMask_data[365];
  boolean_T exitg1;
  int idx_size_idx_0;
  boolean_T idx_data[364];
  double b_data[364];
  int b_s_size[1];
  boolean_T uniquePts_data[365];
  boolean_T x_data[364];
  unsigned int y_data[365];
  short tmp_data[364];
  int y_size[2];
  boolean_T b_tmp_data[365];
  short c_tmp_data[364];
  boolean_T d_tmp_data[365];
  double b_y_data[364];
  int b_y_size[2];
  double b_s_data[364];
  double c_y_data[364];
  double e_tmp_data[364];
  int tmp_size[2];
  diff(A_data, A_size, s_data, s_size);
  nx = s_size[0];
  for (k = 0; k < nx; k++) {
    ctr = s_data[k];
    if (s_data[k] < 0.0) {
      ctr = -1.0;
    } else if (s_data[k] > 0.0) {
      ctr = 1.0;
    } else {
      if (s_data[k] == 0.0) {
        ctr = 0.0;
      }
    }

    s_data[k] = ctr;
  }

  indEnd = A_size[0];
  loop_ub = A_size[0];
  for (i = 0; i < loop_ub; i++) {
    nanMask_data[i] = rtIsNaN(A_data[i]);
  }

  y = false;
  nx = 1;
  exitg1 = false;
  while ((!exitg1) && (nx <= indEnd)) {
    if (!nanMask_data[nx - 1]) {
      nx++;
    } else {
      y = true;
      exitg1 = true;
    }
  }

  if (y) {
    for (i = 0; i <= indEnd - 2; i++) {
      if (nanMask_data[i]) {
        s_data[i] = -1.0;
      }
    }

    loop_ub = A_size[0] - 1;
    idx_size_idx_0 = A_size[0] - 1;
    for (i = 0; i < loop_ub; i++) {
      idx_data[i] = !nanMask_data[i];
    }

    for (i = 0; i < idx_size_idx_0; i++) {
      if (idx_data[i] && nanMask_data[i + 1]) {
        s_data[i] = 1.0;
      }
    }
  }

  y = true;
  nx = 1;
  exitg1 = false;
  while ((!exitg1) && (nx <= s_size[0])) {
    if (s_data[nx - 1] == 0.0) {
      y = false;
      exitg1 = true;
    } else {
      nx++;
    }
  }

  if (!y) {
    loop_ub = s_size[0];
    if (0 <= loop_ub - 1) {
      std::memcpy(&b_data[0], &s_data[0], loop_ub * sizeof(double));
    }

    loop_ub = s_size[0];
    idx_size_idx_0 = s_size[0];
    for (i = 0; i < loop_ub; i++) {
      idx_data[i] = (s_data[i] != 0.0);
    }

    loop_ub = s_size[0];
    indEnd = s_size[0];
    for (i = 0; i < loop_ub; i++) {
      x_data[i] = (s_data[i] != 0.0);
    }

    if (s_size[0] == 0) {
      nx = 0;
    } else {
      nx = x_data[0];
      for (k = 2; k <= indEnd; k++) {
        nx += x_data[k - 1];
      }
    }

    if (nx > 1) {
      if (s_size[0] >= 1) {
        loop_ub = s_size[0] - 1;
        for (i = 0; i <= loop_ub; i++) {
          y_data[i] = static_cast<unsigned int>(i + 1);
        }
      }

      nx = s_size[0] - 1;
      k = 0;
      indEnd = 0;
      for (i = 0; i <= nx; i++) {
        if (s_data[i] != 0.0) {
          k++;
          tmp_data[indEnd] = static_cast<short>(i + 1);
          indEnd++;
        }
      }

      nx = s_size[0] - 1;
      loop_ub = 0;
      indEnd = 0;
      for (i = 0; i <= nx; i++) {
        if (!(s_data[i] != 0.0)) {
          loop_ub++;
          c_tmp_data[indEnd] = static_cast<short>(i + 1);
          indEnd++;
        }
      }

      y_size[0] = 1;
      y_size[1] = k;
      for (i = 0; i < k; i++) {
        b_y_data[i] = y_data[tmp_data[i] - 1];
      }

      b_s_size[0] = k;
      for (i = 0; i < k; i++) {
        b_s_data[i] = s_data[tmp_data[i] - 1];
      }

      b_y_size[0] = 1;
      b_y_size[1] = loop_ub;
      for (i = 0; i < loop_ub; i++) {
        c_y_data[i] = y_data[c_tmp_data[i] - 1];
      }

      interp1(b_y_data, y_size, b_s_data, b_s_size, c_y_data, b_y_size,
              e_tmp_data, tmp_size);
      nx = s_size[0];
      indEnd = 0;
      for (i = 0; i < nx; i++) {
        if (!(b_data[i] != 0.0)) {
          b_data[i] = e_tmp_data[indEnd];
          indEnd++;
        }
      }
    }

    ctr = 0.0;
    nx = 0;
    indEnd = s_size[0];
    for (k = 0; k < idx_size_idx_0; k++) {
      if (idx_data[k]) {
        if (ctr == 0.0) {
          nx = k;
        }

        indEnd = k + 1;
        ctr++;
      }
    }

    if (1 > nx) {
      loop_ub = 0;
    } else {
      loop_ub = nx;
    }

    for (i = 0; i < loop_ub; i++) {
      b_data[i] = s_data[nx];
    }

    if (indEnd + 1 > s_size[0]) {
      i = 0;
      nx = 0;
    } else {
      i = indEnd;
      nx = s_size[0];
    }

    loop_ub = nx - i;
    for (nx = 0; nx < loop_ub; nx++) {
      b_data[i + nx] = s_data[indEnd - 1];
    }

    loop_ub = s_size[0];
    if (0 <= loop_ub - 1) {
      std::memcpy(&s_data[0], &b_data[0], loop_ub * sizeof(double));
    }
  }

  maxVals_size[0] = static_cast<short>(A_size[0]);
  loop_ub = static_cast<short>(A_size[0]);
  if (0 <= loop_ub - 1) {
    std::memset(&maxVals_data[0], 0, loop_ub * sizeof(boolean_T));
  }

  diff(s_data, s_size, b_data, b_s_size);
  loop_ub = b_s_size[0];
  for (i = 0; i < loop_ub; i++) {
    maxVals_data[i + 1] = (b_data[i] < 0.0);
  }

  loop_ub = A_size[0];
  uniquePts_data[0] = true;
  for (i = 0; i <= loop_ub - 2; i++) {
    uniquePts_data[i + 1] = (A_data[i + 1] != A_data[i]);
  }

  loop_ub = A_size[0];
  for (i = 0; i < loop_ub; i++) {
    nanMask_data[i] = rtIsNaN(A_data[i]);
  }

  y = false;
  nx = 1;
  exitg1 = false;
  while ((!exitg1) && (nx <= A_size[0])) {
    if (!nanMask_data[nx - 1]) {
      nx++;
    } else {
      y = true;
      exitg1 = true;
    }
  }

  if (y) {
    loop_ub = A_size[0] - 2;
    indEnd = A_size[0] - 1;
    for (i = 0; i <= loop_ub; i++) {
      nanMask_data[i] = rtIsNaN(A_data[i + 1]);
    }

    loop_ub = A_size[0] - 1;
    for (i = 0; i < loop_ub; i++) {
      b_tmp_data[i] = rtIsNaN(A_data[i]);
    }

    loop_ub = indEnd - 1;
    nx = indEnd + 1;
    d_tmp_data[0] = uniquePts_data[0];
    for (i = 0; i <= loop_ub; i++) {
      d_tmp_data[i + 1] = (uniquePts_data[i + 1] && ((!nanMask_data[i]) ||
        (!b_tmp_data[i])));
    }

    if (0 <= nx - 1) {
      std::memcpy(&uniquePts_data[0], &d_tmp_data[0], nx * sizeof(boolean_T));
    }
  }

  if (1 > s_size[0] - 1) {
    loop_ub = 1;
  } else {
    loop_ub = s_size[0];
  }

  i = (2 <= s_size[0]);
  inflectionPts_size[0] = loop_ub + 1;
  inflectionPts_data[0] = true;
  for (nx = 0; nx <= loop_ub - 2; nx++) {
    inflectionPts_data[nx + 1] = ((s_data[nx] != s_data[i + nx]) &&
      uniquePts_data[nx + 1]);
  }

  inflectionPts_data[loop_ub] = true;
}

//
// Arguments    : const int A_size[1]
//                boolean_T maxVals_data[]
//                const int maxVals_size[1]
//                const double P_data[]
// Return Type  : void
//
static void restrictNumberOfExtrema(const int A_size[1], boolean_T maxVals_data[],
  const int maxVals_size[1], const double P_data[])
{
  int loop_ub;
  int i;
  int trueCount;
  int partialTrueCount;
  unsigned int idx_data[365];
  int x_size[1];
  unsigned int locMaxima_data[365];
  short tmp_data[365];
  double x_data[365];
  int iidx_data[365];
  int iidx_size[1];
  if (A_size[0] >= 1) {
    loop_ub = A_size[0] - 1;
    for (i = 0; i <= loop_ub; i++) {
      idx_data[i] = static_cast<unsigned int>(i + 1);
    }
  }

  loop_ub = maxVals_size[0] - 1;
  trueCount = 0;
  partialTrueCount = 0;
  for (i = 0; i <= loop_ub; i++) {
    if (maxVals_data[i]) {
      trueCount++;
    }

    if (maxVals_data[i]) {
      tmp_data[partialTrueCount] = static_cast<short>(i + 1);
      partialTrueCount++;
    }
  }

  for (i = 0; i < trueCount; i++) {
    locMaxima_data[i] = idx_data[tmp_data[i] - 1];
  }

  x_size[0] = trueCount;
  for (i = 0; i < trueCount; i++) {
    x_data[i] = P_data[static_cast<int>(locMaxima_data[i]) - 1];
  }

  sort(x_data, x_size, iidx_data, iidx_size);
  loop_ub = iidx_size[0];
  for (i = 0; i < loop_ub; i++) {
    x_data[i] = iidx_data[i];
  }

  if (4 > iidx_size[0]) {
    i = 0;
    partialTrueCount = 0;
  } else {
    i = 3;
    partialTrueCount = iidx_size[0];
  }

  loop_ub = partialTrueCount - i;
  for (partialTrueCount = 0; partialTrueCount < loop_ub; partialTrueCount++) {
    iidx_data[partialTrueCount] = static_cast<int>(locMaxima_data[static_cast<
      int>(x_data[i + partialTrueCount]) - 1]);
  }

  for (i = 0; i < loop_ub; i++) {
    maxVals_data[iidx_data[i] - 1] = false;
  }
}

//
// Arguments    : double A[365]
//                boolean_T maxVals[365]
//                double P[365]
// Return Type  : void
//
void b_doLocalMaxSearch(double A[365], boolean_T maxVals[365], double P[365])
{
  int i;
  boolean_T inflectionPts[365];
  boolean_T bv[365];
  boolean_T bv1[365];
  for (i = 0; i < 365; i++) {
    boolean_T b;
    boolean_T b1;
    b = rtIsInf(A[i]);
    bv[i] = b;
    b1 = (A[i] > 0.0);
    bv1[i] = b1;
    if (b && b1) {
      A[i] = rtNaN;
    }
  }

  b_getAllLocalMax(A, maxVals, inflectionPts);
  for (i = 0; i < 365; i++) {
    if (bv[i] && bv1[i]) {
      A[i] = rtInf;
    }

    maxVals[i] = (maxVals[i] || (bv[i] && bv1[i]));
    P[i] = 0.0;
  }

  b_filterByProminence(A, maxVals, P, inflectionPts);
  b_filterByDistance(A, P, maxVals);
  i = maxVals[0];
  for (int k = 0; k < 364; k++) {
    i += maxVals[k + 1];
  }

  if (3 < i) {
    b_restrictNumberOfExtrema(maxVals, P);
  }

  b_adjustFlatRegions(A, maxVals);
}

//
// Arguments    : double A_data[]
//                const int A_size[1]
//                boolean_T maxVals_data[]
//                int maxVals_size[1]
//                double P_data[]
//                int P_size[1]
// Return Type  : void
//
void c_doLocalMaxSearch(double A_data[], const int A_size[1], boolean_T
  maxVals_data[], int maxVals_size[1], double P_data[], int P_size[1])
{
  int loop_ub;
  int nz;
  boolean_T tmp_data[365];
  boolean_T b_tmp_data[365];
  boolean_T inflectionPts_data[365];
  int inflectionPts_size[1];
  P_size[0] = static_cast<short>(A_size[0]);
  loop_ub = static_cast<short>(A_size[0]);
  if (0 <= loop_ub - 1) {
    std::memset(&P_data[0], 0, loop_ub * sizeof(double));
  }

  if (A_size[0] < 3) {
    maxVals_size[0] = static_cast<short>(A_size[0]);
    loop_ub = static_cast<short>(A_size[0]);
    if (0 <= loop_ub - 1) {
      std::memset(&maxVals_data[0], 0, loop_ub * sizeof(boolean_T));
    }
  } else {
    int k;
    nz = A_size[0];
    loop_ub = A_size[0];
    for (k = 0; k < loop_ub; k++) {
      tmp_data[k] = rtIsInf(A_data[k]);
    }

    loop_ub = A_size[0];
    for (k = 0; k < loop_ub; k++) {
      b_tmp_data[k] = (A_data[k] > 0.0);
    }

    for (loop_ub = 0; loop_ub < nz; loop_ub++) {
      if (tmp_data[loop_ub] && b_tmp_data[loop_ub]) {
        A_data[loop_ub] = rtNaN;
      }
    }

    getAllLocalMax(A_data, A_size, maxVals_data, maxVals_size,
                   inflectionPts_data, inflectionPts_size);
    loop_ub = maxVals_size[0];
    for (k = 0; k < loop_ub; k++) {
      maxVals_data[k] = (maxVals_data[k] || (tmp_data[k] && b_tmp_data[k]));
    }

    for (loop_ub = 0; loop_ub < nz; loop_ub++) {
      if (tmp_data[loop_ub] && b_tmp_data[loop_ub]) {
        A_data[loop_ub] = rtInf;
      }
    }

    loop_ub = maxVals_size[0];
    nz = maxVals_data[0];
    for (k = 2; k <= loop_ub; k++) {
      nz += maxVals_data[k - 1];
    }

    if (2 < nz) {
      c_filterByProminence(A_data, A_size, maxVals_data, maxVals_size, P_data,
                           inflectionPts_data);
    }

    loop_ub = maxVals_size[0];
    nz = maxVals_data[0];
    for (k = 2; k <= loop_ub; k++) {
      nz += maxVals_data[k - 1];
    }

    if (2 < nz) {
      c_restrictNumberOfExtrema(A_size, maxVals_data, maxVals_size, P_data);
    }

    adjustFlatRegions(A_data, A_size, maxVals_data, maxVals_size);
  }
}

//
// Arguments    : double A[364]
//                boolean_T maxVals[364]
//                double P[364]
// Return Type  : void
//
void d_doLocalMaxSearch(double A[364], boolean_T maxVals[364], double P[364])
{
  int i;
  boolean_T inflectionPts[364];
  boolean_T isLocMax[364];
  int nz;
  boolean_T bv[364];
  int left;
  short tmp_data[364];
  for (i = 0; i < 364; i++) {
    boolean_T b;
    boolean_T b1;
    P[i] = 0.0;
    b = rtIsInf(A[i]);
    isLocMax[i] = b;
    b1 = (A[i] > 0.0);
    bv[i] = b1;
    if (b && b1) {
      A[i] = rtNaN;
    }
  }

  c_getAllLocalMax(A, maxVals, inflectionPts);
  for (i = 0; i < 364; i++) {
    maxVals[i] = (maxVals[i] || (isLocMax[i] && bv[i]));
    if (isLocMax[i] && bv[i]) {
      A[i] = rtInf;
    }
  }

  nz = maxVals[0];
  for (left = 0; left < 363; left++) {
    nz += maxVals[left + 1];
  }

  if (2 < nz) {
    int trueCount;
    trueCount = 0;
    nz = 0;
    for (i = 0; i < 364; i++) {
      if (maxVals[i] || inflectionPts[i]) {
        trueCount++;
        tmp_data[nz] = static_cast<short>(i + 1);
        nz++;
      }

      isLocMax[i] = maxVals[i];
    }

    for (i = 0; i < trueCount; i++) {
      nz = tmp_data[i] - 1;
      if (isLocMax[nz]) {
        double localMaxValue;
        localMaxValue = A[nz];
        if (rtIsInf(A[nz]) || rtIsNaN(A[nz])) {
          P[nz] = rtInf;
        } else {
          double localMins_idx_0;
          double localMins_idx_1;
          int right;
          int b_i;
          localMins_idx_0 = A[nz];
          localMins_idx_1 = A[nz];
          left = i - 1;
          right = i + 1;
          int exitg3;
          do {
            exitg3 = 0;
            if (left + 1 > 0) {
              b_i = tmp_data[left] - 1;
              if (!isLocMax[b_i]) {
                if ((!(localMins_idx_0 < A[b_i])) && (!rtIsNaN(A[b_i]))) {
                  localMins_idx_0 = A[b_i];
                }

                left--;
              } else if (A[b_i] > localMaxValue) {
                exitg3 = 1;
              } else {
                left--;
              }
            } else {
              exitg3 = 2;
            }
          } while (exitg3 == 0);

          int exitg2;
          do {
            exitg2 = 0;
            if (right + 1 <= trueCount) {
              b_i = tmp_data[right] - 1;
              if (!isLocMax[b_i]) {
                if ((!(localMins_idx_1 < A[b_i])) && (!rtIsNaN(A[b_i]))) {
                  localMins_idx_1 = A[b_i];
                }

                right++;
              } else if (A[b_i] > localMaxValue) {
                exitg2 = 1;
              } else {
                right++;
              }
            } else {
              exitg2 = 1;
            }
          } while (exitg2 == 0);

          if ((localMins_idx_0 < localMins_idx_1) || (rtIsNaN(localMins_idx_0) &&
               (!rtIsNaN(localMins_idx_1)))) {
            localMins_idx_0 = localMins_idx_1;
          }

          P[nz] = A[nz] - localMins_idx_0;
          maxVals[nz] = (P[nz] >= 0.0);
        }
      }
    }
  }

  nz = maxVals[0];
  for (left = 0; left < 363; left++) {
    nz += maxVals[left + 1];
  }

  if (2 < nz) {
    d_restrictNumberOfExtrema(maxVals, P);
  }

  c_adjustFlatRegions(A, maxVals);
}

//
// Arguments    : double A_data[]
//                const int A_size[1]
//                const double x_data[]
//                boolean_T maxVals_data[]
//                int maxVals_size[1]
//                double P_data[]
//                int P_size[1]
// Return Type  : void
//
void doLocalMaxSearch(double A_data[], const int A_size[1], const double x_data[],
                      boolean_T maxVals_data[], int maxVals_size[1], double
                      P_data[], int P_size[1])
{
  int loop_ub;
  int nz;
  boolean_T tmp_data[365];
  boolean_T b_tmp_data[365];
  boolean_T inflectionPts_data[365];
  int inflectionPts_size[1];
  P_size[0] = static_cast<short>(A_size[0]);
  loop_ub = static_cast<short>(A_size[0]);
  if (0 <= loop_ub - 1) {
    std::memset(&P_data[0], 0, loop_ub * sizeof(double));
  }

  if (A_size[0] < 3) {
    maxVals_size[0] = static_cast<short>(A_size[0]);
    loop_ub = static_cast<short>(A_size[0]);
    if (0 <= loop_ub - 1) {
      std::memset(&maxVals_data[0], 0, loop_ub * sizeof(boolean_T));
    }
  } else {
    int k;
    nz = A_size[0];
    loop_ub = A_size[0];
    for (k = 0; k < loop_ub; k++) {
      tmp_data[k] = rtIsInf(A_data[k]);
    }

    loop_ub = A_size[0];
    for (k = 0; k < loop_ub; k++) {
      b_tmp_data[k] = (A_data[k] > 0.0);
    }

    for (loop_ub = 0; loop_ub < nz; loop_ub++) {
      if (tmp_data[loop_ub] && b_tmp_data[loop_ub]) {
        A_data[loop_ub] = rtNaN;
      }
    }

    getAllLocalMax(A_data, A_size, maxVals_data, maxVals_size,
                   inflectionPts_data, inflectionPts_size);
    for (loop_ub = 0; loop_ub < nz; loop_ub++) {
      if (tmp_data[loop_ub] && b_tmp_data[loop_ub]) {
        A_data[loop_ub] = rtInf;
      }
    }

    loop_ub = maxVals_size[0];
    for (k = 0; k < loop_ub; k++) {
      maxVals_data[k] = (maxVals_data[k] || (tmp_data[k] && b_tmp_data[k]));
    }

    filterByProminence(A_data, A_size, maxVals_data, maxVals_size, P_data,
                       inflectionPts_data);
    filterByDistance(A_data, A_size, P_data, maxVals_data, maxVals_size, x_data);
    loop_ub = maxVals_size[0];
    nz = maxVals_data[0];
    for (k = 2; k <= loop_ub; k++) {
      nz += maxVals_data[k - 1];
    }

    if (3 < nz) {
      restrictNumberOfExtrema(A_size, maxVals_data, maxVals_size, P_data);
    }

    adjustFlatRegions(A_data, A_size, maxVals_data, maxVals_size);
  }
}

//
// Arguments    : double A[363]
//                boolean_T maxVals[363]
//                double P[363]
// Return Type  : void
//
void e_doLocalMaxSearch(double A[363], boolean_T maxVals[363], double P[363])
{
  int i;
  boolean_T inflectionPts[363];
  boolean_T isLocMax[363];
  int nz;
  boolean_T bv[363];
  int left;
  short tmp_data[363];
  for (i = 0; i < 363; i++) {
    boolean_T b;
    boolean_T b1;
    P[i] = 0.0;
    b = rtIsInf(A[i]);
    isLocMax[i] = b;
    b1 = (A[i] > 0.0);
    bv[i] = b1;
    if (b && b1) {
      A[i] = rtNaN;
    }
  }

  d_getAllLocalMax(A, maxVals, inflectionPts);
  for (i = 0; i < 363; i++) {
    maxVals[i] = (maxVals[i] || (isLocMax[i] && bv[i]));
    if (isLocMax[i] && bv[i]) {
      A[i] = rtInf;
    }
  }

  nz = maxVals[0];
  for (left = 0; left < 362; left++) {
    nz += maxVals[left + 1];
  }

  if (2 < nz) {
    int trueCount;
    trueCount = 0;
    nz = 0;
    for (i = 0; i < 363; i++) {
      if (maxVals[i] || inflectionPts[i]) {
        trueCount++;
        tmp_data[nz] = static_cast<short>(i + 1);
        nz++;
      }

      isLocMax[i] = maxVals[i];
    }

    for (i = 0; i < trueCount; i++) {
      nz = tmp_data[i] - 1;
      if (isLocMax[nz]) {
        double localMaxValue;
        localMaxValue = A[nz];
        if (rtIsInf(A[nz]) || rtIsNaN(A[nz])) {
          P[nz] = rtInf;
        } else {
          double localMins_idx_0;
          double localMins_idx_1;
          int right;
          int b_i;
          localMins_idx_0 = A[nz];
          localMins_idx_1 = A[nz];
          left = i - 1;
          right = i + 1;
          int exitg3;
          do {
            exitg3 = 0;
            if (left + 1 > 0) {
              b_i = tmp_data[left] - 1;
              if (!isLocMax[b_i]) {
                if ((!(localMins_idx_0 < A[b_i])) && (!rtIsNaN(A[b_i]))) {
                  localMins_idx_0 = A[b_i];
                }

                left--;
              } else if (A[b_i] > localMaxValue) {
                exitg3 = 1;
              } else {
                left--;
              }
            } else {
              exitg3 = 2;
            }
          } while (exitg3 == 0);

          int exitg2;
          do {
            exitg2 = 0;
            if (right + 1 <= trueCount) {
              b_i = tmp_data[right] - 1;
              if (!isLocMax[b_i]) {
                if ((!(localMins_idx_1 < A[b_i])) && (!rtIsNaN(A[b_i]))) {
                  localMins_idx_1 = A[b_i];
                }

                right++;
              } else if (A[b_i] > localMaxValue) {
                exitg2 = 1;
              } else {
                right++;
              }
            } else {
              exitg2 = 1;
            }
          } while (exitg2 == 0);

          if ((localMins_idx_0 < localMins_idx_1) || (rtIsNaN(localMins_idx_0) &&
               (!rtIsNaN(localMins_idx_1)))) {
            localMins_idx_0 = localMins_idx_1;
          }

          P[nz] = A[nz] - localMins_idx_0;
          maxVals[nz] = (P[nz] >= 0.0);
        }
      }
    }
  }

  nz = maxVals[0];
  for (left = 0; left < 362; left++) {
    nz += maxVals[left + 1];
  }

  if (2 < nz) {
    e_restrictNumberOfExtrema(maxVals, P);
  }

  d_adjustFlatRegions(A, maxVals);
}

//
// Arguments    : double A[362]
//                boolean_T maxVals[362]
//                double P[362]
// Return Type  : void
//
void f_doLocalMaxSearch(double A[362], boolean_T maxVals[362], double P[362])
{
  int i;
  boolean_T inflectionPts[362];
  boolean_T isLocMax[362];
  int nz;
  boolean_T bv[362];
  int left;
  short tmp_data[362];
  for (i = 0; i < 362; i++) {
    boolean_T b;
    boolean_T b1;
    P[i] = 0.0;
    b = rtIsInf(A[i]);
    isLocMax[i] = b;
    b1 = (A[i] > 0.0);
    bv[i] = b1;
    if (b && b1) {
      A[i] = rtNaN;
    }
  }

  e_getAllLocalMax(A, maxVals, inflectionPts);
  for (i = 0; i < 362; i++) {
    maxVals[i] = (maxVals[i] || (isLocMax[i] && bv[i]));
    if (isLocMax[i] && bv[i]) {
      A[i] = rtInf;
    }
  }

  nz = maxVals[0];
  for (left = 0; left < 361; left++) {
    nz += maxVals[left + 1];
  }

  if (2 < nz) {
    int trueCount;
    trueCount = 0;
    nz = 0;
    for (i = 0; i < 362; i++) {
      if (maxVals[i] || inflectionPts[i]) {
        trueCount++;
        tmp_data[nz] = static_cast<short>(i + 1);
        nz++;
      }

      isLocMax[i] = maxVals[i];
    }

    for (i = 0; i < trueCount; i++) {
      nz = tmp_data[i] - 1;
      if (isLocMax[nz]) {
        double localMaxValue;
        localMaxValue = A[nz];
        if (rtIsInf(A[nz]) || rtIsNaN(A[nz])) {
          P[nz] = rtInf;
        } else {
          double localMins_idx_0;
          double localMins_idx_1;
          int right;
          int b_i;
          localMins_idx_0 = A[nz];
          localMins_idx_1 = A[nz];
          left = i - 1;
          right = i + 1;
          int exitg3;
          do {
            exitg3 = 0;
            if (left + 1 > 0) {
              b_i = tmp_data[left] - 1;
              if (!isLocMax[b_i]) {
                if ((!(localMins_idx_0 < A[b_i])) && (!rtIsNaN(A[b_i]))) {
                  localMins_idx_0 = A[b_i];
                }

                left--;
              } else if (A[b_i] > localMaxValue) {
                exitg3 = 1;
              } else {
                left--;
              }
            } else {
              exitg3 = 2;
            }
          } while (exitg3 == 0);

          int exitg2;
          do {
            exitg2 = 0;
            if (right + 1 <= trueCount) {
              b_i = tmp_data[right] - 1;
              if (!isLocMax[b_i]) {
                if ((!(localMins_idx_1 < A[b_i])) && (!rtIsNaN(A[b_i]))) {
                  localMins_idx_1 = A[b_i];
                }

                right++;
              } else if (A[b_i] > localMaxValue) {
                exitg2 = 1;
              } else {
                right++;
              }
            } else {
              exitg2 = 1;
            }
          } while (exitg2 == 0);

          if ((localMins_idx_0 < localMins_idx_1) || (rtIsNaN(localMins_idx_0) &&
               (!rtIsNaN(localMins_idx_1)))) {
            localMins_idx_0 = localMins_idx_1;
          }

          P[nz] = A[nz] - localMins_idx_0;
          maxVals[nz] = (P[nz] >= 0.0);
        }
      }
    }
  }

  nz = maxVals[0];
  for (left = 0; left < 361; left++) {
    nz += maxVals[left + 1];
  }

  if (2 < nz) {
    f_restrictNumberOfExtrema(maxVals, P);
  }

  e_adjustFlatRegions(A, maxVals);
}

//
// Arguments    : double A[365]
//                boolean_T maxVals[365]
//                double P[365]
// Return Type  : void
//
void g_doLocalMaxSearch(double A[365], boolean_T maxVals[365], double P[365])
{
  int i;
  boolean_T inflectionPts[365];
  boolean_T isLocMax[365];
  int nz;
  boolean_T bv[365];
  int left;
  short tmp_data[365];
  for (i = 0; i < 365; i++) {
    boolean_T b;
    boolean_T b1;
    P[i] = 0.0;
    b = rtIsInf(A[i]);
    isLocMax[i] = b;
    b1 = (A[i] > 0.0);
    bv[i] = b1;
    if (b && b1) {
      A[i] = rtNaN;
    }
  }

  b_getAllLocalMax(A, maxVals, inflectionPts);
  for (i = 0; i < 365; i++) {
    maxVals[i] = (maxVals[i] || (isLocMax[i] && bv[i]));
    if (isLocMax[i] && bv[i]) {
      A[i] = rtInf;
    }
  }

  nz = maxVals[0];
  for (left = 0; left < 364; left++) {
    nz += maxVals[left + 1];
  }

  if (2 < nz) {
    int trueCount;
    trueCount = 0;
    nz = 0;
    for (i = 0; i < 365; i++) {
      if (maxVals[i] || inflectionPts[i]) {
        trueCount++;
        tmp_data[nz] = static_cast<short>(i + 1);
        nz++;
      }

      isLocMax[i] = maxVals[i];
    }

    for (i = 0; i < trueCount; i++) {
      nz = tmp_data[i] - 1;
      if (isLocMax[nz]) {
        double localMaxValue;
        localMaxValue = A[nz];
        if (rtIsInf(A[nz]) || rtIsNaN(A[nz])) {
          P[nz] = rtInf;
        } else {
          double localMins_idx_0;
          double localMins_idx_1;
          int right;
          int b_i;
          localMins_idx_0 = A[nz];
          localMins_idx_1 = A[nz];
          left = i - 1;
          right = i + 1;
          int exitg3;
          do {
            exitg3 = 0;
            if (left + 1 > 0) {
              b_i = tmp_data[left] - 1;
              if (!isLocMax[b_i]) {
                if ((!(localMins_idx_0 < A[b_i])) && (!rtIsNaN(A[b_i]))) {
                  localMins_idx_0 = A[b_i];
                }

                left--;
              } else if (A[b_i] > localMaxValue) {
                exitg3 = 1;
              } else {
                left--;
              }
            } else {
              exitg3 = 2;
            }
          } while (exitg3 == 0);

          int exitg2;
          do {
            exitg2 = 0;
            if (right + 1 <= trueCount) {
              b_i = tmp_data[right] - 1;
              if (!isLocMax[b_i]) {
                if ((!(localMins_idx_1 < A[b_i])) && (!rtIsNaN(A[b_i]))) {
                  localMins_idx_1 = A[b_i];
                }

                right++;
              } else if (A[b_i] > localMaxValue) {
                exitg2 = 1;
              } else {
                right++;
              }
            } else {
              exitg2 = 1;
            }
          } while (exitg2 == 0);

          if ((localMins_idx_0 < localMins_idx_1) || (rtIsNaN(localMins_idx_0) &&
               (!rtIsNaN(localMins_idx_1)))) {
            localMins_idx_0 = localMins_idx_1;
          }

          P[nz] = A[nz] - localMins_idx_0;
          maxVals[nz] = (P[nz] >= 0.0);
        }
      }
    }
  }

  nz = maxVals[0];
  for (left = 0; left < 364; left++) {
    nz += maxVals[left + 1];
  }

  if (2 < nz) {
    g_restrictNumberOfExtrema(maxVals, P);
  }

  b_adjustFlatRegions(A, maxVals);
}

//
// File trailer for isLocalExtrema.cpp
//
// [EOF]
//
