/*
    Main function of C++ implementation of 3D sound localizer

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2020
 */

#include <iostream>
#include "../include/WAVFile.h"
#include "../include/interpolation.h"
#include "../include/convolution.h"
#include "../include/itd.h"

int main(int, char *argv[]) {
    double theta = std::stod(argv[2]);
    double phi = std::stod(argv[3]);

    std::string source_file = argv[1];
    std::string output_file = argv[4];

    WAVFile HRIR = hrir_interpolation(theta, phi);
    WAVFile source = WAVFile(source_file);

    std::vector<double> convolved_left = convolve(source.left, HRIR.left);
    std::vector<double> convolved_right = convolve(source.right, HRIR.right);

    int itd = calculate_delay(theta, source.sample_rate);

    std::vector<double> left;
    std::vector<double> right;

    if (itd <= 0) {
        right.resize(abs(itd), 0);
        right.insert(right.end(), convolved_right.begin(), convolved_right.end());

        left = convolved_left;
        left.resize(left.size() + abs(itd), 0);
    } else {
        left.resize(itd, 0);
        left.insert(left.end(), convolved_left.begin(), convolved_left.end());

        right = convolved_right;
        right.resize(right.size() + itd, 0);
    }

    WAVFile output = WAVFile();
    output.left = left;
    output.right = right;

    output.channels = 2;
    output.format = source.format;
    output.frames = left.size();

    int status = output.write(output_file);
    if (!status) {
        std::cout << "New file successfully written!" << std::endl;
    } else {
        std::cout << "Writing failed!" << std::endl;
    }

    return 0;
}
