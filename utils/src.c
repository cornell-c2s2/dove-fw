#include "src.h"
#include "arith.h"
#include "stdio.h"

// Preprocessing code
// void normalize(float *data, size_t num_samples, double targetPeak)
// {
//   // Check for zero samples to avoid division by zero
//   if (num_samples == 0)
//   {
//     fprintf(stderr, "Error: num_samples is zero.\n");
//     return;
//   }
//   // Find the loudest point
//   float loudest_point = 0;
//   // Iterate to find the largest sample in magnitude
//   for (size_t i = 0; i < num_samples; i++)
//   {
//     if (fabsf(data[i]) > loudest_point)
//     {
//       loudest_point = fabsf(data[i]);
//     }
//   }
//   // Calculate the normalization factor
//   double normalization_factor = targetPeak / loudest_point;

//   // Normalize each sample
//   for (size_t i = 0; i < num_samples; i++)
//   {
//     data[i] = (float)(data[i] * 100);
//   }
// }

// void hamming_window(float *data, size_t num_samples)
// {
//   // Check for zero samples to avoid division by zero
//   if (num_samples == 0)
//   {
//     fprintf(stderr, "Error: num_samples is zero.\n");
//     return;
//   }

//   // Apply Hamming
//   for (size_t i = 0; i < num_samples; i++)
//   {
//     double window_value = 0.54 - (0.46 * cos(2.0 * PI * i / (num_samples - 1)));
//     data[i] = (float)(data[i] * window_value);
//   }
// }

// Wrap up hamming and normalization
// float *preprocess(const char signed *samples, size_t numSamples)
// {

//   // Allocate memory to store the PCM data as integers
//   int16_t *pcmDataInt = (int16_t *)malloc(numSamples * sizeof(int16_t));

//   if (pcmDataInt == NULL)
//   {
//     fprintf(stderr, "Memory allocation error\n");
//     return NULL;
//   }

//   // Copy samples to pcmDataInt
//   for (size_t i = 0; i < numSamples; i++)
//   {
//     pcmDataInt[i] = (int16_t)samples[i];
//   }

//   // Convert integer PCM data to float
//   float *pcmDataFloat = (float *)malloc(numSamples * sizeof(float));

//   if (pcmDataFloat == NULL)
//   {
//     fprintf(stderr, "Memory allocation error\n");
//     free(pcmDataInt);
//     return NULL;
//   }

//   for (size_t i = 0; i < numSamples; i++)
//   {
//     // Not sure if it needs to be / INT16_MAX
//     pcmDataFloat[i] = (float)pcmDataInt[i]; // Assuming 16-bit PCM
//   }

//   // Now 'pcmDataFloat' contains the PCM data as floating-point values
//   // Normalize and apply hamming

//   // Commented out because of hardcoded header
//   //  normalize(pcmDataFloat, numSamples, .0);

//   hamming_window(pcmDataFloat, numSamples);

//   free(pcmDataInt);

//   return pcmDataFloat;
// }

// Old matched filter
void matched_filter(char *input_signal, int signal_length, char *filter_kernel, int kernel_length, char *filtered_signal)
{
  // Allocate memory for the filtered signal
  // N + M - 1
  int filtered_length = signal_length + kernel_length - 1;

  for (int i = 0; i < filtered_length; ++i)
  {
    filtered_signal[i] = 0.0;

    for (int j = 0; j < kernel_length; ++j)
    {
      if (i >= j && i - j < signal_length)
      {
        filtered_signal[i] += mul (input_signal[i - j], filter_kernel[kernel_length - 1 - j]);
      }
    }
  }
}


// New matched filter for board
// For filtered_signal: 
// Entries 0 to num_samples - 1 contain data with noise (AKA actual data)
// Entries num_samples to kernel_length - 1 contain the template signal to match with
// Entries kernel_length to num_samples + kernel_length - 2 contain the result of the matched filter
// It is the duty of the caller to make sure there is enough space in the ptr. 
void new_matched_filter(char *filtered_signal,int signal_length, int kernel_length)
{
  // Get length of the output signal: N + M - 1
  int filtered_length = signal_length + kernel_length - 1;

  // Starting index for putting matched filter results
  int start = signal_length + kernel_length;

  for (int i = 0; i < filtered_length; ++i)
  {
    for (int j = 0; j < kernel_length; ++j)
    {
      if (i >= j && i - j < signal_length)
      {
        filtered_signal[start + i] += mul (filtered_signal[i - j], filtered_signal[signal_length + (kernel_length - 1 - j)]);
      }
    }
    // printf("Match entry: %d num: %d\n", start+i,filtered_signal[start+i] );
  }
}