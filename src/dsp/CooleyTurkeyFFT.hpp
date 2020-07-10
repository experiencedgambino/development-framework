// https://www.drdobbs.com/cpp/a-simple-and-efficient-fft-implementatio/199500857
#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>

inline void four1(double* data, unsigned long nn)
{
    unsigned long n, mmax, m, j, istep, i;
    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;

    // reverse-binary reindexing
    n = nn<<1;
    j=1;
    for (i=1; i<n; i+=2) {
        if (j>i) {
            std::swap(data[j-1], data[i-1]);
            std::swap(data[j], data[i]);
        }
        m = nn;
        while (m>=2 && j>m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    };

    // here begins the Danielson-Lanczos section
    mmax=2;
    while (n>mmax) {
        istep = mmax<<1;
        theta = -(2*M_PI/mmax);
        wtemp = sin(0.5*theta);
        wpr = -2.0*wtemp*wtemp;
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for (m=1; m < mmax; m += 2) {
            for (i=m; i <= n; i += istep) {
                j=i+mmax;
                tempr = wr*data[j-1] - wi*data[j];
                tempi = wr * data[j] + wi*data[j-1];

                data[j-1] = data[i-1] - tempr;
                data[j] = data[i] - tempi;
                data[i-1] += tempr;
                data[i] += tempi;
            }
            wtemp=wr;
            wr += wr*wpr - wi*wpi;
            wi += wi*wpr + wtemp*wpi;
        }
        mmax=istep;
    }
}

void dft_attempt(std::complex<double> * data, std::size_t size)
{

} // dft_attempt


std::shared_ptr<std::vector<std::complex<double>>> fft(double * data, std::size_t size)
{
  std::shared_ptr<std::vector<std::complex<double>>> return_ptr
    = std::make_shared<std::vector<std::complex<double>>>(ß);

  if (size % 2 != 0)
  {
    std::cout << "Number of elements must be power of 2" << std::endl;
    return false;
  } // if

  return_ptr = std::make_shared<
}



// Assumes output and data are same
std::shared_ptr< fft_attempt(double * data, double * output, std::size_t stride = 1)
{


  if (size <= 2)
  {
    return dft_attempt(data, size/2);
  } // if

  fft_attempt(data, stride * 2);
  fft_attempt(data + stride, stride * 2);

  T even {0.0};
  T odd {0.0};
  for (std::size_t subfft_index = 0; subfft_index < size/2; subfft_index+=(stride*2))
  {
    even = std::exp(std::complex<double>(0, -2 * math.PI));
    *(data)
  } // for
  // terms = np.exp(-2j * np.pi * np.arange(N) / N)
        // return np.concatenate([X_even + terms[:int(N/2)] * X_odd,
                               // X_even + terms[int(N/2):] * X_odd])
} // fft_attempt
