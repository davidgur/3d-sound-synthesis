/*
    convolution.cpp implements the convolve function, which convolves two vectors using the overlap-add method.

    Author: David Gurevich (dgurevic (at) uwaterloo (dot) ca)

    Copyright (c) David Gurevich 2021
 */

#include "../include/convolution.h"

std::vector<double> convolve(const std::vector<double> &signal, std::vector<double> filter) {
    const int M = 512;
    const int N = 4096;
    const int step_size = N - (M - 1);
    int Nx = signal.size();
    int position = 0;

    // Calculate DFT of filter
    filter.resize(N, 0);
    fftw_complex H[(N / 2) + 1] = {{0.0, 0.0}};
    fftw_plan p_filter = fftw_plan_dft_r2c_1d(N, filter.data(), H, FFTW_ESTIMATE);
    fftw_execute(p_filter);

    // Define output
    std::vector<double> y(Nx, 0);

    // Make FFT plan for X
    double in_fft[N] = {0.0};
    fftw_complex out_fft[N] = {{0.0, 0.0}};
    fftw_plan p_x = fftw_plan_dft_r2c_1d(N, in_fft, out_fft, FFTW_ESTIMATE);

    // Make IFFT plan for y
    fftw_complex in_ifft[N] = {{0.0, 0.0}};
    double out_ifft[N] = {0.0};
    fftw_plan p_y = fftw_plan_dft_c2r_1d(N, in_ifft, out_ifft, FFTW_ESTIMATE);


    while (position + step_size <= Nx) {
        // Fill x (in_fft)
        for (int i = position; i < position + step_size; i++) {
            in_fft[i - position] = signal[i];
        }
        fftw_execute(p_x);

        // Fill H*x (in_ifft)
        for (int i = 0; i < N; i++) {
            in_ifft[i][REAL] = (out_fft[i][REAL] * H[i][REAL]) - (out_fft[i][COMP] * H[i][COMP]);
            in_ifft[i][COMP] = (out_fft[i][REAL] * H[i][COMP]) + (out_fft[i][COMP] * H[i][REAL]);
        }

        fftw_execute(p_y);

        for (int i = 0; i < N; i++) {
            y[position + i] += out_ifft[i];
        }

        position += step_size;
    }

    // One more to get the remaining bit
    for (int i = position; i < Nx; i++) {
        in_fft[i - position] = signal[i];
    }
    for (int i = Nx; i < N; i++) {
        in_fft[i] = 0;
    }
    fftw_execute(p_x);

    // Fill H*x
    for (int i = 0; i < N; i++) {
        in_ifft[i][REAL] = (out_fft[i][REAL] * H[i][REAL]) - (out_fft[i][COMP] * H[i][COMP]);
        in_ifft[i][COMP] = (out_fft[i][REAL] * H[i][COMP]) + (out_fft[i][COMP] * H[i][REAL]);
    }
    fftw_execute(p_y);

    for (int i = 0; i < Nx - position; i++) {
        y[position + i] += out_ifft[i];
    }


    fftw_destroy_plan(p_filter);
    fftw_destroy_plan(p_x);
    fftw_destroy_plan(p_y);

    for (auto &elem : y) { elem /= N; }

    return y;
}
