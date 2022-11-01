//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: interp1.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//

// Include Files
#include "interp1.h"
#include "NDVI46to365.h"
#include "phen_6method.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Declarations
static void b_interp1Step(const double y_data[], int nyrows, const double
  xi_data[], const int xi_size[1], double yi_data[], const double
  varargin_1_data[], const int varargin_1_size[1]);
static void interp1Step(const double y_data[], const double xi_data[], const int
  xi_size[2], double yi_data[], const double varargin_1_data[], const int
  varargin_1_size[2]);

// Function Definitions

//
// Arguments    : const double y_data[]
//                int nyrows
//                const double xi_data[]
//                const int xi_size[1]
//                double yi_data[]
//                const double varargin_1_data[]
//                const int varargin_1_size[1]
// Return Type  : void
//
static void b_interp1Step(const double y_data[], int nyrows, const double
  xi_data[], const int xi_size[1], double yi_data[], const double
  varargin_1_data[], const int varargin_1_size[1])
{
  double minx;
  double maxx;
  int ub_loop;
  int high_i;
  int low_i;
  int low_ip1;
  int mid_i;
  minx = varargin_1_data[0];
  maxx = varargin_1_data[varargin_1_size[0] - 1];
  ub_loop = xi_size[0] - 1;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(high_i,low_i,low_ip1,mid_i)

  for (int k = 0; k <= ub_loop; k++) {
    if (rtIsNaN(xi_data[k])) {
      yi_data[k] = rtNaN;
    } else if (xi_data[k] > maxx) {
      yi_data[k] = y_data[nyrows - 1];
    } else if (xi_data[k] < minx) {
      yi_data[k] = y_data[0];
    } else {
      high_i = varargin_1_size[0];
      low_i = 1;
      low_ip1 = 2;
      while (high_i > low_ip1) {
        mid_i = (low_i >> 1) + (high_i >> 1);
        if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
          mid_i++;
        }

        if (xi_data[k] >= varargin_1_data[mid_i - 1]) {
          low_i = mid_i;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }

      if (!(xi_data[k] >= (varargin_1_data[low_i] + varargin_1_data[low_i - 1]) /
            2.0)) {
        low_i--;
      }

      yi_data[k] = y_data[low_i];
    }
  }
}

//
// Arguments    : const double y_data[]
//                const double xi_data[]
//                const int xi_size[2]
//                double yi_data[]
//                const double varargin_1_data[]
//                const int varargin_1_size[2]
// Return Type  : void
//
static void interp1Step(const double y_data[], const double xi_data[], const int
  xi_size[2], double yi_data[], const double varargin_1_data[], const int
  varargin_1_size[2])
{
  double minx;
  double maxx;
  int ub_loop;
  double d;
  int high_i;
  int low_i;
  int low_ip1;
  int mid_i;
  minx = varargin_1_data[0];
  maxx = varargin_1_data[varargin_1_size[1] - 1];
  ub_loop = xi_size[1] - 1;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(d,high_i,low_i,low_ip1,mid_i)

  for (int k = 0; k <= ub_loop; k++) {
    d = xi_data[k];
    if (rtIsNaN(d)) {
      yi_data[k] = rtNaN;
    } else if (d > maxx) {
      yi_data[k] = rtNaN;
    } else if (d < minx) {
      yi_data[k] = y_data[0];
    } else {
      high_i = varargin_1_size[1];
      low_i = 1;
      low_ip1 = 2;
      while (high_i > low_ip1) {
        mid_i = (low_i >> 1) + (high_i >> 1);
        if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
          mid_i++;
        }

        if (xi_data[k] >= varargin_1_data[mid_i - 1]) {
          low_i = mid_i;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }

      if (!(xi_data[k] > varargin_1_data[low_i - 1])) {
        low_i--;
      }

      yi_data[k] = y_data[low_i];
    }
  }
}

//
// Arguments    : const double varargin_1_data[]
//                const int varargin_1_size[1]
//                const double varargin_2_data[]
//                const int varargin_2_size[1]
//                const double varargin_3_data[]
//                const int varargin_3_size[1]
//                double Vq_data[]
//                int Vq_size[1]
// Return Type  : void
//
void b_interp1(const double varargin_1_data[], const int varargin_1_size[1],
               const double varargin_2_data[], const int varargin_2_size[1],
               const double varargin_3_data[], const int varargin_3_size[1],
               double Vq_data[], int Vq_size[1])
{
  int n;
  double y_data[545];
  int x_size[1];
  double x_data[545];
  int nx;
  n = varargin_2_size[0];
  if (0 <= n - 1) {
    std::memcpy(&y_data[0], &varargin_2_data[0], n * sizeof(double));
  }

  x_size[0] = varargin_1_size[0];
  n = varargin_1_size[0];
  if (0 <= n - 1) {
    std::memcpy(&x_data[0], &varargin_1_data[0], n * sizeof(double));
  }

  nx = varargin_1_size[0] - 1;
  Vq_size[0] = static_cast<short>(varargin_3_size[0]);
  n = static_cast<short>(varargin_3_size[0]);
  if (0 <= n - 1) {
    std::memset(&Vq_data[0], 0, n * sizeof(double));
  }

  if (varargin_3_size[0] != 0) {
    int k;
    k = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (k <= nx) {
        if (rtIsNaN(varargin_1_data[k])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (varargin_1_data[1] < varargin_1_data[0]) {
          double xtmp;
          int nd2;
          n = (nx + 1) >> 1;
          for (k = 0; k < n; k++) {
            xtmp = x_data[k];
            nd2 = nx - k;
            x_data[k] = x_data[nd2];
            x_data[nd2] = xtmp;
          }

          if ((varargin_2_size[0] != 0) && (varargin_2_size[0] > 1)) {
            n = varargin_2_size[0] - 1;
            nd2 = varargin_2_size[0] >> 1;
            for (k = 0; k < nd2; k++) {
              xtmp = y_data[k];
              nx = n - k;
              y_data[k] = y_data[nx];
              y_data[nx] = xtmp;
            }
          }
        }

        b_interp1Step(y_data, varargin_2_size[0], varargin_3_data,
                      varargin_3_size, Vq_data, x_data, x_size);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

//
// Arguments    : const double varargin_1_data[]
//                const int varargin_1_size[2]
//                const double varargin_2_data[]
//                const int varargin_2_size[1]
//                const double varargin_3_data[]
//                const int varargin_3_size[2]
//                double Vq_data[]
//                int Vq_size[2]
// Return Type  : void
//
void interp1(const double varargin_1_data[], const int varargin_1_size[2], const
             double varargin_2_data[], const int varargin_2_size[1], const
             double varargin_3_data[], const int varargin_3_size[2], double
             Vq_data[], int Vq_size[2])
{
  int n;
  double y_data[364];
  int x_size[2];
  double x_data[364];
  int nx;
  short outsize_idx_1;
  double b_x_data[545];
  n = varargin_2_size[0];
  if (0 <= n - 1) {
    std::memcpy(&y_data[0], &varargin_2_data[0], n * sizeof(double));
  }

  x_size[0] = 1;
  x_size[1] = varargin_1_size[1];
  n = varargin_1_size[0] * varargin_1_size[1];
  if (0 <= n - 1) {
    std::memcpy(&x_data[0], &varargin_1_data[0], n * sizeof(double));
  }

  nx = varargin_1_size[1] - 1;
  outsize_idx_1 = static_cast<short>(varargin_3_size[1]);
  Vq_size[0] = 1;
  Vq_size[1] = outsize_idx_1;
  n = outsize_idx_1;
  if (0 <= n - 1) {
    std::memset(&Vq_data[0], 0, n * sizeof(double));
  }

  if (varargin_3_size[1] != 0) {
    int k;
    k = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (k <= nx) {
        if (rtIsNaN(varargin_1_data[k])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (varargin_1_data[1] < varargin_1_data[0]) {
          int b_j1;
          double xtmp;
          int x_tmp;
          n = (nx + 1) >> 1;
          for (b_j1 = 0; b_j1 < n; b_j1++) {
            xtmp = x_data[b_j1];
            x_tmp = nx - b_j1;
            x_data[b_j1] = x_data[x_tmp];
            x_data[x_tmp] = xtmp;
          }

          b_j1 = varargin_2_size[0];
          n = varargin_2_size[0];
          if (0 <= n - 1) {
            std::memcpy(&b_x_data[0], &varargin_2_data[0], n * sizeof(double));
          }

          if ((varargin_2_size[0] != 0) && (varargin_2_size[0] > 1)) {
            n = varargin_2_size[0] - 1;
            nx = varargin_2_size[0] >> 1;
            for (k = 0; k < nx; k++) {
              xtmp = b_x_data[k];
              x_tmp = n - k;
              b_x_data[k] = b_x_data[x_tmp];
              b_x_data[x_tmp] = xtmp;
            }
          }

          if (0 <= b_j1 - 1) {
            std::memcpy(&y_data[0], &b_x_data[0], b_j1 * sizeof(double));
          }
        }

        interp1Step(y_data, varargin_3_data, varargin_3_size, Vq_data, x_data,
                    x_size);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

//
// Arguments    : const double y[46]
//                const double xi[365]
//                double yi[365]
//                const double varargin_1[46]
// Return Type  : void
//
void interp1Linear(const double y[46], const double xi[365], double yi[365],
                   const double varargin_1[46])
{
  double minx;
  double penx;
  double maxx;
  int low_i;
  int low_ip1;
  int high_i;
  double r;
  int mid_i;
  minx = varargin_1[0];
  penx = varargin_1[44];
  maxx = varargin_1[45];

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(low_i,low_ip1,high_i,r,mid_i)

  for (int k = 0; k < 365; k++) {
    if (xi[k] > maxx) {
      yi[k] = y[45] + (xi[k] - maxx) / (maxx - penx) * (y[45] - y[44]);
    } else if (xi[k] < minx) {
      yi[k] = y[0] + (xi[k] - minx) / (varargin_1[1] - minx) * (y[1] - y[0]);
    } else {
      low_i = 1;
      low_ip1 = 2;
      high_i = 46;
      while (high_i > low_ip1) {
        mid_i = (low_i + high_i) >> 1;
        if (xi[k] >= varargin_1[mid_i - 1]) {
          low_i = mid_i;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }

      r = varargin_1[low_i - 1];
      r = (xi[k] - r) / (varargin_1[low_i] - r);
      if (r == 0.0) {
        yi[k] = y[low_i - 1];
      } else if (r == 1.0) {
        yi[k] = y[low_i];
      } else if (y[low_i - 1] == y[low_i]) {
        yi[k] = y[low_i - 1];
      } else {
        yi[k] = (1.0 - r) * y[low_i - 1] + r * y[low_i];
      }
    }
  }
}

//
// File trailer for interp1.cpp
//
// [EOF]
//
