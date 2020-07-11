#include "CooleyTurkeyFFT.hpp"

int main()
{
  double * input = (double *) malloc(1024);
  double * output = (double *) malloc(1024);

  fft(input, output, 1024);
} // main
