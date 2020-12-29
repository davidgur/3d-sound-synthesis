/*
    Main function of C++ implementation of 3D sound localizer

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2020
 */

#include <iostream>
#include "../include/localize.h"

int main(int, char *argv[]) {
    double theta = std::stod(argv[2]);
    double phi = std::stod(argv[3]);

    std::string source_file = argv[1];
    std::string output_file = argv[4];

    WAVFile source = WAVFile(source_file);
    WAVFile output = localize(source, theta, phi);

    int status = output.write(output_file);
    if (!status) {
        std::cout << "New file successfully written!" << std::endl;
    } else {
        std::cout << "Writing failed!" << std::endl;
    }

    return 0;
}
