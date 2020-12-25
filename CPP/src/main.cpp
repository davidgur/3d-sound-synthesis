/*
    Main function of C++ implementation of 3D sound localizer

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2020
 */

#include <iostream>
#include "../include/WAVFile.h"
#include "../include/interpolation.h"

int main(int, char *argv[]) {
    WAVFile HRIR = hrir_interpolation(37, 0);

    std::cout << HRIR.summary() << std::endl;

    return 0;
}
