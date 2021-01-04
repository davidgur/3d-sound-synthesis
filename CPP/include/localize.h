/*
    All-in-one function that localizes a given WAVFile to a particular position

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2021
 */

#ifndef CPP_LOCALIZE_H
#define CPP_LOCALIZE_H

#include "../include/WAVFile.h"
#include "../include/interpolation.h"
#include "../include/convolution.h"
#include "../include/itd.h"

WAVFile localize(const WAVFile &source, double theta, double phi, bool use_itd);

#endif //CPP_LOCALIZE_H
