/*
    Main function of C++ implementation of 3D sound localizer

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2020
 */

#include <iostream>
#include "../include/demo.h"

int main(int, char *argv[]) {
    double theta = std::stod(argv[2]);
    double phi = std::stod(argv[3]);

    bool demo_mode = false;

    if (theta == 0 && phi == 0) {
        demo_mode = true;
    }

    std::string source_file = argv[1];
    std::string output_file = argv[4];

    WAVFile source = WAVFile(source_file);
    WAVFile output;

    if (demo_mode)
        output = demo(source, 10, 5);
    else
        output = localize(source, theta, phi, true);

    int status = output.write(output_file);
    if (!status) {
        std::cout << "New file successfully written!" << std::endl;
    } else {
        std::cout << "Writing failed!" << std::endl;
    }

    return 0;
}
