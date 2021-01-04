/*
    Implementations of functions for WAVFile class

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2021
 */

#include "../include/WAVFile.h"

WAVFile::WAVFile() {
    format = 65538;
    frames = 0;
    channels = 2;
    sample_rate = 44100;
}

WAVFile::WAVFile(const std::string &file_name) {
    std::filesystem::path path = file_name;
    if (std::filesystem::is_regular_file(path)) {
        SndfileHandle my_file = SndfileHandle(&path.string()[0]);

        frames = my_file.frames();
        format = my_file.format();
        channels = my_file.channels();
        sample_rate = my_file.samplerate();

        std::vector<double> data(frames * 2);

        left = std::vector<double>(frames);
        right = std::vector<double>(frames);

        my_file.read(&data[0], frames * channels);

        bool toggle = false;
        std::partition_copy(data.begin(), data.end(),
                            left.begin(),
                            right.begin(),
                            [&toggle](int) { return toggle = !toggle; }
        );
    }
}

int WAVFile::write(const std::string &name) const {
    std::vector<double> merged = merge_left_right(left, right);

    if (merged.empty()) {
        return 1;
    }

    SndfileHandle file = SndfileHandle(name, SFM_WRITE, format, channels, sample_rate);
    if (file.write(&merged[0], merged.size()) == merged.size())
        return 0;
    else
        return 1;
}

std::vector<double> WAVFile::merge_left_right(const std::vector<double> &left, const std::vector<double> &right) {
    if (left.size() != right.size())
        return std::vector<double>();
    else {
        std::vector<double> merged(left.size() + right.size(), 0);

        for (int i = 0; i < merged.size(); i += 2) {
            merged[i] = left[i / 2];
            merged[i + 1] = right[i / 2];
        }

        return merged;
    }
}

const std::string WAVFile::summary() {
    std::string header_text = "[WAV FILE SUMMARY]\n";
    std::string format_text = "\t Format: " + std::to_string(format) + "\n";
    std::string channel_text = "\t Channels: " + std::to_string(channels) + "\n";
    std::string frames_text = "\t Frames: " + std::to_string(frames) + "\n";
    std::string sample_rate_text = "\t Sampling Rate: " + std::to_string(sample_rate) + "\n";
    std::string duration_text = "\t Duration: " + std::to_string(frames / sample_rate) + "s. \n";

    std::string summary = header_text + format_text + channel_text + frames_text + sample_rate_text + duration_text;
    return summary;
}

