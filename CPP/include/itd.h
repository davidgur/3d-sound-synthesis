/*
    itd.h defines the itd function, which calculates interaural time delay between left and right audio tracks

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2020
 */

#ifndef CPP_ITD_H
#define CPP_ITD_H

#include <cmath>

#define HEAD_RADIUS 0.0875
#define SPEED_SOUND 343

int calculate_delay(double theta, int sample_rate);

#endif //CPP_ITD_H
