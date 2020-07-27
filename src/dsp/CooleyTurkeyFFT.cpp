#include "CooleyTurkeyFFT.hpp"

const std::complex<double> CooleyTurkeyFFT::dftSizeTwoMatrix[2][2] {
  {std::complex<double>(1.0,0.0), std::complex<double>(1.0,0.0)},
  {std::complex<double>(1.0,0.0), std::exp(std::complex<double>(0, CooleyTurkeyFFT::dftSizeTwoExponentialConstant))},
};
const double CooleyTurkeyFFT::dftSizeTwoExponentialConstant = -M_PI;

void CooleyTurkeyFFT::dft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size, std::size_t stride)
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

void CooleyTurkeyFFT::idft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size, std::size_t stride)
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

// Assumes output and data are same size
void CooleyTurkeyFFT::fft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size, std::size_t stride)
{
  if (size <= 2)
  {
    dft_size_two(input, output, stride);
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

// Assumes output and data are same size
void CooleyTurkeyFFT::ifft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size)
{
  /*
  For an inverse FFT, run the same algorithm as a normal
  FFT, but then reverse the order of the output elements,
  starting at index of 1
  */
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
} // ifft_attempt

bool CooleyTurkeyFFT::fft(double * input,  std::complex<double> * output, std::size_t size)
{
  bool return_value {true};

  // Compute if size divisible by 2
  if (ceil(log2((float)size)) == floor(log2((float)size)))
  {
    std::complex<double> * input_complex = (std::complex<double> *) malloc(size * sizeof(std::complex<double>));

    // Need to convert real input data to complex format
    for (std::size_t input_counter = 0; input_counter < size; ++input_counter)
    {
      input_complex[input_counter].imag(0.0);
      input_complex[input_counter].real(input[input_counter]);
    } // for

    // Run complex FFT
    fft_attempt(input_complex, output, size, 1);

    // Free the allocated data
    free(input_complex);
  } // if
  else
  {
    return_value = false;
  } // else

  return return_value;
} // fft

bool CooleyTurkeyFFT::ifft(std::complex<double> * input,  std::complex<double> * output, std::size_t size)
{
  // Only run if size is power of 2
  if (ceil(log2((float)size)) == floor(log2((float)size)))
  {
    ifft_attempt(input, output, size);
    return true;
  } // if
  else
  {
    return false;
  } // else
}


void CooleyTurkeyFFT::dft_size_two(std::complex<double> * input, std::complex<double> * output, std::size_t stride)
{
  // Loop over each index in the DFT to calculate
  for (std::size_t k_counter = 0; k_counter < 2; ++k_counter)
  {
    // Need to ensure value is zero to start
    output[k_counter*stride] = std::complex<double>(0,0);

    // Loop over each sample in the input data
    for (std::size_t n_counter = 0; n_counter < 2; ++n_counter)
    {
      output[k_counter*stride] += input[n_counter * stride] * CooleyTurkeyFFT::dftSizeTwoMatrix[k_counter][n_counter];
    } // for
  } // for
}
