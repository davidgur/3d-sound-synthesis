/*
    itd.cpp implements a function which calculates interaural time delay between left and right audio tracks

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2021
 */

#include "../include/itd.h"

int calculate_delay(double theta, int sample_rate) {
    int left_delay = 0;
    int right_delay = 0;

    if (theta == 360 || theta == 180) {
        left_delay = 0;
        right_delay = 0;
    } else if (0 < theta && theta < 180) {
        left_delay = sample_rate * (-HEAD_RADIUS * sin(theta * M_PI / 180)) / SPEED_SOUND;
        right_delay = sample_rate * (HEAD_RADIUS * (theta * M_PI / 180)) / SPEED_SOUND;
    } else if (180 < theta && theta < 360) {
        left_delay = sample_rate * (HEAD_RADIUS * (theta * M_PI / 180)) / SPEED_SOUND;
        right_delay = sample_rate * (-HEAD_RADIUS * sin(theta * M_PI / 180)) / SPEED_SOUND;
    }

    int itd_samples = left_delay - right_delay;

    return itd_samples;
}
