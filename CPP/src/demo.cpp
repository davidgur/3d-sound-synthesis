//
// Created by david on 12/28/20.
//

#include "../include/demo.h"
#include <iostream>

std::vector<std::vector<double>> split_vector(const std::vector<double> &total, int num_splits) {
    int bunch_size = static_cast<int>(total.size() / num_splits);

    std::vector<std::vector<double>> bunches;
    bunches.reserve((total.size() + 1) / bunch_size);

    for (size_t i = 0; i < total.size(); i += bunch_size) {
        auto last = std::min(total.size(), i + bunch_size);
        bunches.emplace_back(total.begin() + i, total.begin() + last);
    }

    return bunches;
}

std::vector<WAVFile> split_wav(const WAVFile &source, int num_splits) {
    std::vector<WAVFile> split(num_splits);

    std::vector<std::vector<double>> left_chunks = split_vector(source.left, num_splits);
    std::vector<std::vector<double>> right_chunks = split_vector(source.right, num_splits);

    for (int i = 0; i < num_splits; i++) {
        split[i].left = left_chunks[i];
        split[i].right = right_chunks[i];

        split[i].sample_rate = source.sample_rate;
        split[i].channels = source.channels;
        split[i].format = source.format;
        split[i].frames = split[i].left.size();
    }

    return split;
}

WAVFile wav_flatten(const std::vector<WAVFile> &split) {
    WAVFile flattened;

    std::vector<double> left;
    std::vector<double> right;

    // build left and right
    for (auto &wav : split) {
        left.insert(left.end(), wav.left.begin(), wav.left.end());
        right.insert(right.end(), wav.right.begin(), wav.right.end());
    }

    flattened.left = left;
    flattened.right = right;

    flattened.sample_rate = split[0].sample_rate;
    flattened.channels = 2;
    flattened.format = split[0].format;
    flattened.frames = left.size();

    return flattened;
};

WAVFile demo(const WAVFile &source, int revs, double theta_interval) {
    int num_of_sections = static_cast<int>(360 * revs / theta_interval);

    auto split = split_wav(source, num_of_sections);
    std::vector<WAVFile> localized_split(num_of_sections);

    for (int i = 0; i < split.size(); i++) {
        localized_split[i].left = std::move(split[i].left);
        localized_split[i].right = std::move(split[i].right);
        localized_split[i].channels = 2;
        localized_split[i].sample_rate = split[i].sample_rate;
        localized_split[i].format = split[i].format;
        localized_split[i].frames = split[i].left.size();

        double theta = std::fmod(theta_interval * i, 360);

        localized_split[i] = localize(localized_split[i], theta, 0, false);
    }

    WAVFile flattened = wav_flatten(localized_split);

    return flattened;
}
