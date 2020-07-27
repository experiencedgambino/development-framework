#include <algorithm>
#include <cmath>
#include <complex>

class CooleyTurkeyFFT
{
public:
  static void dft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size, std::size_t stride = 1);
  static void idft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size, std::size_t stride);
  static void fft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size, std::size_t stride);
  static void ifft_attempt(std::complex<double> * input, std::complex<double> * output, std::size_t size);
  static bool fft(double * input,  std::complex<double> * output, std::size_t size);
  static bool ifft(std::complex<double> * input,  std::complex<double> * output, std::size_t size);
  static void dft_size_two(std::complex<double> * input, std::complex<double> * output, std::size_t stride = 1);

private:
  static const std::complex<double> dftSizeTwoMatrix[2][2];
  static const double dftSizeTwoExponentialConstant;
}; // CooleyTurkeyFFT
