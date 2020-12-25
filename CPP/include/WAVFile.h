/*
    WAVFile.h contains the class WAVFile, which allows for simple
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
    WAVFile(const std::string &file_name);

    // Write function
    int write(const std::string &name);

    // Header Data
    int frames;
    int format;
    int channels;
    int sample_rate;

    // Data
    std::vector<double> left;
    std::vector<double> right;

    bool read_complete = false;

private:
    std::vector<double> merge_left_right(const std::vector<double> &left, const std::vector<double> &right);
};


#endif //CPP_WAVFILE_H
