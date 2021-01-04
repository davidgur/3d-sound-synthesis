/*
    Functions that allow for a "demo mode" which makes the given audio sound as though it is circling around the user.

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2021
 */


#ifndef CPP_DEMO_H
#define CPP_DEMO_H

#include <vector>
#include <cmath>

#include "../include/localize.h"

std::vector<std::vector<double>> split_vector(const std::vector<double> &total, int num_splits);

std::vector<WAVFile> split_wav(const WAVFile &source, int num_splits);

WAVFile wav_flatten(const std::vector<WAVFile> &split);

WAVFile demo(const WAVFile &source, int revs, double theta_interval);

#endif //CPP_DEMO_H
