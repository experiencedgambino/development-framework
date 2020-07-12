#include "CooleyTurkeyFFT.hpp"

int main()
{
  int size = 8;
  double * input = (double *) malloc(size * sizeof(double));
  double * output = (double *) malloc(size * sizeof(double));

  for (int i = 0; i < size; ++i)
  {
    input[i] = i;
  } // for

  fft(input, output, size);

  for (int i = 0; i < size; ++i)
  {
    std::cout << output[i] << std::endl;
  } // for
} // main
