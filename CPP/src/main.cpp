/*
    Main function of C++ implementation of 3D sound localizer

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2020
 */

#include <iostream>
#include "../include/WAVFile.h"

int main(int, char *argv[]) {
    WAVFile sound_file = WAVFile(argv[1]);

    std::cout << "WAV File Specifications:" << std::endl;
    std::cout << "\tChannels: " << sound_file.channels << std::endl;
    std::cout << "\tSample Rate: " << sound_file.sample_rate << std::endl;
    std::cout << "\tDuration: " << sound_file.left.size() / sound_file.sample_rate << " seconds" << std::endl;

    if (sound_file.write("data/wav_test/write_test.wav")) {
        std::cout << "Error writing new WAV file!" << std::endl;
    }

    return 0;
}
