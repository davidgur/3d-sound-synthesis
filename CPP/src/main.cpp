/*
    Main function of C++ implementation of 3D sound localizer

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2020
 */

#include <iostream>
#include "../include/WAVFile.h"
#include "../include/interpolation.h"
#include "../include/convolution.h"

int main(int, char *argv[]) {
    WAVFile HRIR = hrir_interpolation(std::stod(argv[2]), std::stod(argv[3]));
    WAVFile sound = WAVFile(argv[1]);

    std::vector<double> left = convolve(sound.left, HRIR.left);
    std::vector<double> right = convolve(sound.right, HRIR.right);

    WAVFile convolved = WAVFile();
    convolved.left = left;
    convolved.right = right;

    convolved.channels = 2;
    convolved.format = sound.format;
    convolved.frames = left.size();

    int status = convolved.write(argv[4]);
    if (!status) {
        std::cout << "New file successfully written!" << std::endl;
    } else {
        std::cout << "Writing failed!" << std::endl;
    }

    return 0;
}
