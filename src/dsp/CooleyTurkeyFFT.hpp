// https://www.drdobbs.com/cpp/a-simple-and-efficient-fft-implementatio/199500857
#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>

void dft_attempt(double * input, std::complex<double> * output, std::size_t size, std::size_t stride);
void fft_attempt(double * input, std::complex<double> * output, std::size_t size, std::size_t stride);

bool fft(double * input, double * output, std::size_t size)
{
  bool return_value {true};

  // Compute if size divisible by 2
  if (size % 2 == 0)
  {
    std::complex<double> * output_complex = (std::complex<double> *) malloc(size * sizeof(std::complex<double>));
    fft_attempt(input, output_complex, size, 1);
    for (int i = 0; i < size; ++i)
    {
      output[i] = std::abs(output_complex[i]);
    } // for
  } // if
  else
  {
    return_value = false;
  } // else

  return return_value;
} // fft

void dft_attempt(double * input, std::complex<double> * output, std::size_t size, std::size_t stride)
{
  // Outer loop calculates each value of the DFT
  for (std::size_t k_counter = 0; k_counter < size; ++k_counter)
  {
    // Inner loop - iterate over samples
    std::complex<double> temp;
    output[k_counter*stride] = std::complex<double>(0,0);
    for (std::size_t n_counter = 0; n_counter < size; ++n_counter)
    {
      output[k_counter*stride] += input[n_counter * stride] * std::exp(std::complex<double>(0, -2 * M_PI * (double)k_counter * n_counter / size));
    } // for
  } // for
} // dft_attempt

// Assumes output and data are same
void fft_attempt(double * input, std::complex<double> * output, std::size_t size, std::size_t stride)
{
  if (size <= 2)
  {
    dft_attempt(input, output, size, stride);
    return;
  } // if

  fft_attempt(input, output, size / 2, stride * 2);
  fft_attempt(input + stride, output+stride, size / 2, stride * 2);

  std::complex<double> * temp = (std::complex<double> *) malloc(size * sizeof(std::complex<double>));
  for (std::size_t k_index = 0; k_index < size; ++k_index)
  {
    temp[k_index] = std::complex<double>(0,0);
    temp[k_index] = output[ ((k_index%size) * stride*2) % (stride*size)] + std::exp(std::complex<double>(0, -2.0 * M_PI * k_index / size)) * output[(stride+((k_index)*stride)*2) % (stride*size)];
  } // for

  for (std::size_t k_index = 0; k_index < size; ++k_index)
  {
    output[k_index * stride] = temp[k_index];
  } // for

  free(temp);
} // fft_attempt
