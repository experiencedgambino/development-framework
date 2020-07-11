// https://www.drdobbs.com/cpp/a-simple-and-efficient-fft-implementatio/199500857
#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>

bool fft_attempt(double * input, double * output, std::size_t size, std::size_t stride);

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


bool fft(double * input, double * output, std::size_t size)
{
  bool return_value {true};
  if (size % 2 == 0)
  {
    // Process if size divisible by 2
    fft_attempt(input, output, size, 1);
  } // if
} // fft

void dft_attempt(double * input, double * output, std::size_t size, std::size_t stride)
{
  // Outer loop calculates each value of the DFT
  for (std::size_t k_counter = 0; k_counter < size; ++k_counter)
  {
    output[k_counter] = 0;
    // Inner loop
    for (std::size_t n_counter = 0; n_counter < size; ++n_counter)
    {
      output[k_counter] += input[k_counter] * cos((2 * M_PI / size) * k_counter * n_counter);
    } // for
  } // for
} // dft_attempt

// Assumes output and data are same
bool fft_attempt(double * input, double * output, std::size_t size, std::size_t stride)
{
  bool return_value {true};
  if (size <= 2)
  {
    dft_attempt(input, output, size, stride);
  } // if

  std::cout << "(Size, Stride) (" << size << "," << stride << ")" << std::endl;

  std::this_thread

  fft_attempt(input, output, size / 2, stride * 2);
  fft_attempt(input + stride, output, size / 2, stride * 2);

  double * temp = (double *) malloc(size * sizeof(double));
  // for (std::size_t k_index = 0; k_index < size/2; k_index+=(stride*2))
  // {
  //   temp[k_index] = output[k_index * stride * 2] + (double) cos(-2.0 * M_PI * k_index / size) * output[stride+(k_index*stride*2)];
  // } // for

  free(temp);

  return return_value;
} // fft_attempt





/*

  Xn           [0]   [1]   [2]   [3]   [4]   [5]   [6]   [7]

  Keven        [0]         [2]         [4]         [6]
  Kodd               [1]         [3]         [5]         [7]

 K[0]          [0]   [1]
 K[1]                      [2]   [3]
 K[2]                                  [4]   [5]
 K[3]                                              [6]   [7]
 K[4]          [0]   [1]
 K[5]                      [2]   [3]
 K[6]                                  [4]   [5]
 K[7]                                              [6]   [7]

*/
