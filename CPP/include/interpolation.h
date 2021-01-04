/*
    interpolation.h contains functions and values necessary for bilinear interpolation of HRIR filters (in WAV files)

    The dataset used in this project to get the HRIR is quite sparse.
    However, we want to be able to determine the HRIR at any given location.
    We are able to do this by interpolating the HRIR functions that are
    provided by our dataset. This is done using the generalized bilinear
    interpolation method as described in "Interpolation of Head-Related
    Transfer Frunctions (HRTFS): A Multi-Source approach" by Freeland,
    Biscainho, and Diniz.

    Freeland, F. P., Biscainho, L. W., & Diniz, P. S. (2004, September).
    Interpolation of head-related transfer functions (HRTFs): A multi-source
    approach. In 2004 12th European Signal Processing Conference
    (pp. 1761-1764). IEEE.

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2021
 */

#ifndef CPP_INTERPOLATION_H
#define CPP_INTERPOLATION_H

#include "../include/WAVFile.h"

// Constants
static const std::vector<int> possible_phi = {-45, -30, -15, 0, 15, 30, 45, 60, 75};

// Functions
WAVFile hrir_interpolation(double theta, double phi);

WAVFile load_hrir(double theta, double phi);

std::vector<int> get_possible_theta(int phi);

std::vector<double> vector_sum(const std::vector<double> &A,
                               const std::vector<double> &B,
                               const std::vector<double> &C);

std::vector<double> best_fit_line(const std::vector<double> &vec);

void scale_vector(double scalar, std::vector<double> &vec);

int get_prev_phi(double phi);

int get_nearest_phi(double phi);

int get_next_phi(double phi);

int get_prev_theta(double theta, double phi);

int get_nearest_theta(double theta, double phi);

int get_next_theta(double theta, double phi);

#endif //CPP_INTERPOLATION_H
