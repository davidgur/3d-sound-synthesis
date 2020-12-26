/*
    convolution.h defines the convolve function, which is used to convolve an audio signal with a FIR filter using
        the overlap-add method (https://en.wikipedia.org/wiki/Overlap%E2%80%93add_method)

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2020
 */

#ifndef CPP_CONVOLUTION_H
#define CPP_CONVOLUTION_H

#include <fftw3.h>
#include <vector>
#include <complex>

#define REAL 0
#define COMP 1

std::vector<double> convolve(const std::vector<double> &signal, std::vector<double> filter);

#endif //CPP_CONVOLUTION_H
