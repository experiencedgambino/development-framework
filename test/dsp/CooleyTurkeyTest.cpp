#include "CooleyTurkeyFFT.hpp"
#include <iostream>

int main()
{
  int size = 16;
  std::complex<double> * input = (std::complex<double> *) malloc(size * sizeof(std::complex<double>));
  std::complex<double> * output = (std::complex<double> *) malloc(size * sizeof(std::complex<double>));
  std::complex<double> * input_reclaimed = (std::complex<double> *) malloc(size * sizeof(std::complex<double>));

  for (int i = 0; i < size; ++i)
  {
    input[i].real(i+1);
  } // for

  CooleyTurkeyFFT::fft_attempt(input, output, size, 1);
  CooleyTurkeyFFT::ifft_attempt(output, input_reclaimed, size);

  for (int i = 0; i < size; ++i)
  {
    std::cout << input[i] << "," << input_reclaimed[i] << std::endl;
  } // for
} // main
