#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>

void dft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size, std::size_t stride);
void idft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size, std::size_t stride);
void fft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size, std::size_t stride);
bool ifft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size, std::size_t stride);

bool fft(double * input, double * output, std::size_t size)
{
  bool return_value {true};

  // Compute if size divisible by 2
  if (ceil(log2((float)size)) == floor(log2((float)size)))
  {
    std::complex<double> * output_complex = (std::complex<double> *) malloc(size * sizeof(std::complex<double>));
    std::complex<double> * input_complex = (std::complex<double> *) malloc(size * sizeof(std::complex<double>));

    // Need to convert real input data to complex format
    for (std::size_t input_counter = 0; input_counter < size; ++input_counter)
    {
      input_complex[input_counter].real(input[input_counter]);
    } // for

    // Run complex FFT
    fft_attempt(input_complex, output_complex, size, 1);

    // Place magnitude of complex FFT output into output data
    for (std::size_t k_index = 0; k_index < size; ++k_index)
    {
      output[k_index] = std::abs(output_complex[k_index]);
    } // for

    free(output_complex);
    free(input_complex);
  } // if
  else
  {
    return_value = false;
  } // else


  return return_value;
} // fft

bool fft(double * input,  std::complex<double> * output, std::size_t size)
{
  bool return_value {true};

  // Compute if size divisible by 2
  if (size % 2 == 0)
  {
    std::complex<double> * input_complex = (std::complex<double> *) malloc(size * sizeof(std::complex<double>));

    // Need to convert real input data to complex format
    for (std::size_t input_counter = 0; input_counter < size; ++input_counter)
    {
      input_complex[input_counter].real(input[input_counter]);
    } // for

    // Run complex FFT
    fft_attempt(input_complex, output, size, 1);

    free(input_complex);
  } // if
  else
  {
    return_value = false;
  } // else

  return return_value;
} // fft

void dft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size, std::size_t stride = 1)
{
  // Saves computational time for this calculation in the exponential
  double exponential_constant = -2 * M_PI / size;

  // Loop over each index in the DFT to calculate
  for (std::size_t k_counter = 0; k_counter < size; ++k_counter)
  {
    // Need to ensure value is zero to start
    output[k_counter*stride] = std::complex<double>(0,0);

    // Loop over each sample in the input data
    for (std::size_t n_counter = 0; n_counter < size; ++n_counter)
    {
      output[k_counter*stride] += input[n_counter * stride] * std::exp(std::complex<double>(0, exponential_constant * k_counter * n_counter));
    } // for
  } // for
} // dft_attempt

void idft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size, std::size_t stride)
{
  // Saves computational time for this calculation in the exponential
  double exponential_constant = 2 * M_PI / size;

  // Loop over each index in the DFT to calculate
  for (std::size_t n_counter = 0; n_counter < size; ++n_counter)
  {
    // Need to ensure value is zero to start
    output[n_counter*stride] = std::complex<double>(0,0);

    // Loop over each sample in the input data
    for (std::size_t k_counter = 0; k_counter < size; ++k_counter)
    {
      output[n_counter*stride] += input[k_counter * stride] * std::exp(std::complex<double>(0, exponential_constant * k_counter * n_counter));
    } // for

    output[n_counter*stride] /= size;
  } // for
} // dft_attempt

// Assumes output and data are same
void fft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size, std::size_t stride)
{
  if (size <= 2)
  {
    dft_attempt(input, output, size, stride);
    return;
  } // if

  // Values that are calculated twice
  std::size_t stride_times_two = stride * 2;
  std::size_t size_over_two = size / 2;
  std::size_t stride_times_size = stride * size;

  // Calculate the FFT in two halves
  //    Using the even indices of current FFT
  fft_attempt(input, output, size_over_two, stride_times_two);
  //    Using the off indices of the current FFT
  fft_attempt(input + stride, output+stride, size_over_two, stride_times_two);

  // As of now, we need a temporary vector to store the output values
  std::complex<double> * temp = (std::complex<double> *) malloc(size * sizeof(std::complex<double>));

  // Saves computational time for this calculation in the exponential
  double exponential_constant = -2.0 * M_PI / size;

  // Iterate across each index of the output FFT vector
  for (std::size_t k_index = 0; k_index < size; ++k_index)
  {
    temp[k_index] = output[ (k_index * stride_times_two) % stride_times_size]
                  + std::exp(std::complex<double>(0, exponential_constant * k_index))
                  * output[(stride+(k_index*stride_times_two)) % stride_times_size];
  } // for

  // As of now, we need to copy the temporary vector into the output vector.
  // Cannot use memcpy because values usually are not contiguous due to stride.
  for (std::size_t k_index = 0; k_index < size; ++k_index)
  {
    output[k_index * stride] = temp[k_index];
  } // for

  // Free allocated temporary vector
  free(temp);
} // fft_attempt

// Assumes output and data are same
bool ifft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size)
{
  /*
  For an inverse FFT, run the same algorithm as a normal
  FFT, but then reverse the order of the output elements,
  starting at index of 1
  */

  // Only run if size is power of 2
  if (ceil(log2((float)size)) == floor(log2((float)size)))
  {
    fft_attempt(input, output, size, 1);

    // Reverse order of input samples
    for (std::size_t k_index = 1; k_index < size / 2; ++k_index)
    {
      std::swap(output[k_index], output[size - k_index]);
    } // if

    // Needs to be divided by the size to return to original samples
    for (std::size_t k_index = 0; k_index < size; ++k_index)
    {
      output[k_index] /= size;
    } // if
    return true;
  } // if
  else
  {
    return false;
  } // else

} // ifft_attempt
