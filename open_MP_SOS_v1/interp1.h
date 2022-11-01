//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: interp1.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 22-Apr-2020 15:12:37
//
#ifndef INTERP1_H
#define INTERP1_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "NDVI46to365_types.h"
#define MAX_THREADS                    omp_get_max_threads()

// Function Declarations
extern void b_interp1(const double varargin_1_data[], const int varargin_1_size
                      [1], const double varargin_2_data[], const int
                      varargin_2_size[1], const double varargin_3_data[], const
                      int varargin_3_size[1], double Vq_data[], int Vq_size[1]);
extern void interp1(const double varargin_1_data[], const int varargin_1_size[2],
                    const double varargin_2_data[], const int varargin_2_size[1],
                    const double varargin_3_data[], const int varargin_3_size[2],
                    double Vq_data[], int Vq_size[2]);
extern void interp1Linear(const double y[46], const double xi[365], double yi
  [365], const double varargin_1[46]);

#endif

//
// File trailer for interp1.h
//
// [EOF]
//
