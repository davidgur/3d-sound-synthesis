/*
    interpolation.h contains functions and values necessary for bilinear interpolation of HRIR filters (in WAV files)

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2020
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

void scale_vector(double scalar, std::vector<double> &vec);

int get_prev_phi(double phi);

int get_nearest_phi(double phi);

int get_next_phi(double phi);

int get_prev_theta(double theta, double phi);

int get_nearest_theta(double theta, double phi);

int get_next_theta(double theta, double phi);

#endif //CPP_INTERPOLATION_H
