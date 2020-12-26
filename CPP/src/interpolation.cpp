/*
    Definitions for functions necessary for interpolation of HRIR filters (stored in WAV files)

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2020
 */

#include "../include/interpolation.h"


WAVFile hrir_interpolation(double theta, double phi) {
    double A_phi = get_next_phi(phi);
    double B_phi = A_phi;
    double C_phi = get_prev_phi(A_phi);

    double A_theta = get_next_theta(theta, A_phi);
    double B_theta = get_prev_theta(theta, B_phi);
    double C_theta = get_nearest_theta(theta, C_phi);

    if (A_theta == B_theta && B_theta == C_theta) {
        return load_hrir(theta, phi);
    }

    double delta_theta_grid = B_theta - A_theta;
    double delta_theta_A = theta - A_theta;
    double delta_theta_AC = C_theta - A_theta;

    double delta_phi_grid = C_phi - A_phi;
    double delta_phi = phi - A_phi;

    double W_C = delta_phi / delta_phi_grid;
    double W_B = (delta_theta_A - W_C * delta_theta_AC) / delta_theta_grid;
    double W_A = 1 - W_B - W_C;

    // Load HRIR A, B, and C
    WAVFile A = load_hrir(A_theta, A_phi);
    WAVFile B = load_hrir(B_theta, B_phi);
    WAVFile C = load_hrir(C_theta, C_phi);

    scale_vector(W_A, A.left);
    scale_vector(W_A, A.right);
    scale_vector(W_B, B.left);
    scale_vector(W_B, B.right);
    scale_vector(W_C, C.left);
    scale_vector(W_C, C.right);

    // Build new HRIR
    WAVFile HRIR = WAVFile();

    HRIR.left = vector_sum(A.left, B.left, C.left);
    HRIR.right = vector_sum(A.right, B.right, C.right);

    HRIR.frames = HRIR.left.size();

    return HRIR;
}

WAVFile load_hrir(double theta, double phi) {
    std::vector<int> possible_theta = get_possible_theta(phi);

    bool theta_possible = std::find(possible_theta.begin(), possible_theta.end(), theta) != possible_theta.end();
    bool phi_possible = std::find(possible_phi.begin(), possible_phi.end(), phi) != possible_phi.end();

    if (!theta_possible || !phi_possible) {
        return WAVFile();
    }

    if (phi < 0) phi += 360;

    std::stringstream phi_ss;
    phi_ss << std::setw(3) << std::setfill('0') << phi;

    std::stringstream theta_ss;
    theta_ss << std::setw(3) << std::setfill('0') << theta;

    std::string file_name = "data/IRC_1020_C/IRC_1020_C_R0195_T" +
                            theta_ss.str() + "_P" +
                            phi_ss.str() + ".wav";

    return WAVFile(file_name);
}

std::vector<int> get_possible_theta(int phi) {
    std::vector<int> possible_theta;

    // build phi to have a width of 3
    std::stringstream ss;
    ss << std::setw(3) << std::setfill('0') << phi;
    std::string phi_str = ss.str();

    std::string path = "data/IRC_1020_C/";
    for (auto &p: std::filesystem::directory_iterator(path)) {
        std::string file_name = p.path().filename();
        if (file_name.find("P" + phi_str) != std::string::npos) {
            int theta = std::stoi(file_name.substr(18, 3));
            possible_theta.push_back(theta);
        }
    }

    std::sort(possible_theta.begin(), possible_theta.end());

    return possible_theta;
}

int get_prev_phi(double phi) {
    for (auto i = possible_phi.rbegin(); i != possible_phi.rend(); i++) {
        if (*i < phi)
            return *i;
    }
    return 0;
}

int get_nearest_phi(double phi) {
    const auto lower_it = std::lower_bound(possible_phi.begin(), possible_phi.end(), phi);
    const auto upper_it = std::upper_bound(possible_phi.begin(), possible_phi.end(), phi);

    if (abs(*lower_it - phi) < abs(*upper_it - phi)) {
        return *lower_it;
    } else {
        return *upper_it;
    }
}

int get_next_phi(double phi) {
    for (auto i = possible_phi.begin(); i != possible_phi.end(); i++) {
        if (*i > phi)
            return *i;
    }
    return 0;
}

int get_prev_theta(double theta, double phi) {
    std::vector<int> possible_theta = get_possible_theta(phi);

    for (auto i = possible_theta.rbegin(); i != possible_theta.rend(); i++) {
        if (*i < theta)
            return *i;
    }
    return 0;
}

int get_nearest_theta(double theta, double phi) {
    std::vector<int> possible_theta = get_possible_theta(phi);

    const auto lower_it = std::lower_bound(possible_theta.begin(), possible_theta.end(), theta);
    const auto upper_it = std::upper_bound(possible_theta.begin(), possible_theta.end(), theta);

    if (abs(*lower_it - theta) < abs(*upper_it - theta)) {
        return *lower_it;
    } else {
        return *upper_it;
    }
}

int get_next_theta(double theta, double phi) {
    std::vector<int> possible_theta = get_possible_theta(phi);

    for (auto i = possible_theta.begin(); i != possible_theta.end(); i++) {
        if (*i > theta)
            return *i;
    }
    return 0;
}

std::vector<double>
vector_sum(const std::vector<double> &A, const std::vector<double> &B, const std::vector<double> &C) {
    if (A.size() != B.size() || B.size() != C.size()) {
        return std::vector<double>(0);
    }

    std::vector<double> sum(A.size(), 0);

    for (int i = 0; i < A.size(); i++) {
        sum[i] = A[i] + B[i] + C[i];
    }

    return sum;
}

void scale_vector(double scalar, std::vector<double> &vec) {
    std::transform(vec.begin(), vec.end(), vec.begin(), [&scalar](double &c) { return c * scalar; });
};
