#include "CooleyTurkeyFFT.hpp"

int main()
{
  int size = 65536;
  double * input = (double *) malloc(size * sizeof(double));
  double * output = (double *) malloc(size * sizeof(double));

  double interval = 2 * M_PI / size;

  for (int i = 0; i < size; ++i)
  {
    input[i] = sin(10000 * i * interval);
  } // for

  fft(input, output, size);

  for (int i = 0; i < size; ++i)
  {
    std::cout << sin(4 * i * interval) << "," << output[i] << std::endl;
  } // for
} // main
