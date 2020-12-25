/*
    WAVFile.h contains the class WAVFile, which allows for simple reading and writing of a .wav file.

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2020
 */

#ifndef CPP_WAVFILE_H
#define CPP_WAVFILE_H

#include <sndfile.hh>
#include <cstring>
#include <filesystem>
#include <vector>

class WAVFile {
public:
    // Constructor
    explicit WAVFile(const std::string &file_name);

    // Write function
    [[nodiscard]] int write(const std::string &name) const;

    // Header Data
    int frames;
    int format;
    int channels;
    int sample_rate;

    // Data
    std::vector<double> left;
    std::vector<double> right;

private:
    static std::vector<double> merge_left_right(const std::vector<double> &left, const std::vector<double> &right);
};


#endif //CPP_WAVFILE_H
