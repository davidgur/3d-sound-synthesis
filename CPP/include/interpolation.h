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
WAVFile hrir_interpolation(int theta, int phi);

WAVFile load_hrir(int theta, int phi);

std::vector<int> get_possible_theta(int phi);

std::vector<double> vector_sum(const std::vector<double> &A,
                               const std::vector<double> &B,
                               const std::vector<double> &C);

void scale_vector(double scalar, std::vector<double> &vec);

int get_prev_phi(int phi);

int get_nearest_phi(int phi);

int get_next_phi(int phi);

int get_prev_theta(int theta, int phi);

int get_nearest_theta(int theta, int phi);

int get_next_theta(int theta, int phi);

#endif //CPP_INTERPOLATION_H
