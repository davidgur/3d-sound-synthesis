/*
    All-in-one function that localizes a given WAVFile to a particular position

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2020
 */
#include "../include/localize.h"

WAVFile localize(const WAVFile &source, double theta, double phi, bool use_itd) {
    WAVFile HRIR = hrir_interpolation(theta, phi);

    std::vector<double> convolved_left = convolve(source.left, HRIR.left);
    std::vector<double> convolved_right = convolve(source.right, HRIR.right);

    int itd = calculate_delay(theta, source.sample_rate);

    std::vector<double> left;
    std::vector<double> right;

    if (use_itd) {
        if (itd <= 0) {
            right.resize(abs(itd), 0);
            right.insert(right.end(), convolved_right.begin(), convolved_right.end());

            left = std::move(convolved_left);
            left.resize(left.size() + abs(itd), 0);
        } else {
            left.resize(itd, 0);
            left.insert(left.end(), convolved_left.begin(), convolved_left.end());

            right = std::move(convolved_right);
            right.resize(right.size() + itd, 0);
        }
    } else {
        left = std::move(convolved_left);
        right = std::move(convolved_right);
    }

    WAVFile output = WAVFile();

    output.left = left;
    output.right = right;
    output.channels = source.channels;
    output.format = source.format;
    output.frames = left.size();

    return output;
}
