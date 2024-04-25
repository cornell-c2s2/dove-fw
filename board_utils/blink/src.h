#ifndef SRC_H
#define SRC_H

// #include <stddef.h>
// #include <stdio.h>
// #include <stdint.h>
// #include <math.h>
// #include <stdlib.h>
// #include <sndfile.h>
// #include </home/elias/spectrogram_software/bird_2.h>
#define PI 3.14159265358979323846

/// @brief A simple function that normalizes audio using Peak Normalization.
/// It finds the highest peak, calculates the normalization factor,
/// and then multiplies each entry by the normalization factor.
/// This is a preprocessing function.
/// @param data  A float pointer for the PCM samples.
/// @param num_samples An int representing the number of samples in the array,
/// must be greater than 0.
/// @param targetPeak A double that represents the target peak wanted.
// void normalize(float *data, size_t num_samples, double targetPeak);

/// @brief A simple hamming function used when preprocessing the audio.
/// This will prepare the data for the FFT. As of now it is best to apply
/// normalization first. This is a preprocesssing function.
/// @param data A float pointer for the PCM samples.
/// @param num_samples An int representing the number of samples in the array,
/// must be greater than 0.
// void hamming_window(float *data, size_t num_samples);

/// @brief preprocess wraps the all the preprocessing functions.
/// @param samples A short pointer that represents the pcm samples.
/// @param numSamples The number of samples with respect to the pointer given.
/// @return a pointer with the samples given being converted to floats.
// float *preprocess(const char signed *samples, size_t numSamples);


/// @brief Implements a matched filter by computing the convolution. Returns
/// an array of floats that represents the correlation.
/// @param input_signal The array of PCM samples representing the input signal.
/// @param signal_length The length of the input signal.
/// @param filter_kernel The array representing the template for the matched filter.
/// @param kernel_length The length of the filter kernel
void matched_filter(int *input_signal, int signal_length, int *filter_kernel, int kernel_length, int *filtered_signal);

#endif