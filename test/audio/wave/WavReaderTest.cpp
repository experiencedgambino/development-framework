#include "CooleyTurkeyFFT.hpp"
#include "WavReader.hpp"

#include <complex>
#include <chrono>
#include <iostream>

#define REQUIRED_ARG_NUM 3
#define WAVEFILE_PATH_ARG 1
#define OUTPUT_PATH_ARG 2

#define FFT_SECTOR_SIZE 32
#define NUM_MINS_TO_ELIMINATE 16

int main(int argc, char ** argv)
{
  if (argc != REQUIRED_ARG_NUM)
  {
    std::cout << "Usage: WaveTest [path to wav file] [output wav file]" << std::endl;
    return -1;
  } // if

  WavReader reader;

  reader.Read(argv[WAVEFILE_PATH_ARG]);
  reader.GetStream(std::cout);
  // 
  // // Convert arrays to double
  // double * channel_one_double_array = (double *) malloc(reader.DataSize() * sizeof(double));
  // double * channel_two_double_array = (double *) malloc(reader.DataSize() * sizeof(double));
  // for (std::size_t counter = 0; counter < reader.DataSize(); ++counter)
  // {
  //   channel_one_double_array[counter] = reader.GetSample(counter, WavReader::Channel_e::CHANNEL_ONE);
  //   channel_two_double_array[counter] = reader.GetSample(counter, WavReader::Channel_e::CHANNEL_TWO);
  // } // for
  // //
  // // Take the FFT of each sector of specified size
  // std::complex<double> * output = (std::complex<double> *) malloc(FFT_SECTOR_SIZE * sizeof(std::complex<double>));
  // std::complex<double> * input_compressed = (std::complex<double> *) malloc(FFT_SECTOR_SIZE * sizeof(std::complex<double>));
  // double * magnitude_output = (double *) malloc(FFT_SECTOR_SIZE * sizeof(double));
  // for (std::size_t sector_counter = 0; sector_counter < (reader.DataSize() / FFT_SECTOR_SIZE); ++sector_counter)
  // {
  //   std::size_t output_start = (sector_counter * FFT_SECTOR_SIZE);
  //
  //   // CHANNEL 1 calculations
  //   if (CooleyTurkeyFFT::fft(channel_one_double_array+output_start, output, FFT_SECTOR_SIZE) == false)
  //   {
  //     std::cout << "Cannot take FFT chan 1" << std::endl;
  //   } // if
  //   for (std::size_t k_counter = 0; k_counter < FFT_SECTOR_SIZE; ++k_counter)
  //   {
  //     magnitude_output[k_counter] = std::abs(output[k_counter]);
  //   } // for
  //   for (std::size_t min_counter = 0; min_counter < NUM_MINS_TO_ELIMINATE; ++min_counter)
  //   {
  //     std::size_t minimum_output = std::min_element(magnitude_output, magnitude_output+FFT_SECTOR_SIZE) - magnitude_output;
  //     magnitude_output[minimum_output] = std::numeric_limits<double>().max();
  //     output[minimum_output] = std::complex<double>(0,0);
  //   } // for
  //   CooleyTurkeyFFT::ifft_attempt(output, input_compressed, FFT_SECTOR_SIZE);
  //   for(std::size_t n_counter = 0; n_counter < FFT_SECTOR_SIZE; ++n_counter)
  //   {
  //     reader.SetSample(output_start + n_counter, WavReader::Channel_e::CHANNEL_ONE, input_compressed[n_counter].real());
  //   } // for
  //
  //   // CHANNEL 2 calculations
  //   if (CooleyTurkeyFFT::fft(channel_two_double_array+output_start, output, FFT_SECTOR_SIZE) == false)
  //   {
  //     std::cout << "Cannot take FFT chan 2" << std::endl;
  //   } // if
  //
  //   for (std::size_t k_counter = 0; k_counter < FFT_SECTOR_SIZE; ++k_counter)
  //   {
  //     magnitude_output[k_counter] = std::abs(output[k_counter]);
  //   } // for
  //
  //   for (std::size_t min_counter = 0; min_counter < NUM_MINS_TO_ELIMINATE; ++min_counter)
  //   {
  //     std::size_t minimum_output = std::min_element(magnitude_output, magnitude_output+FFT_SECTOR_SIZE) - magnitude_output;
  //     magnitude_output[minimum_output] = std::numeric_limits<double>().max();
  //     output[minimum_output] = std::complex<double>(0,0);
  //   } // for
  //
  //   CooleyTurkeyFFT::ifft_attempt(output, input_compressed, FFT_SECTOR_SIZE);
  //   for(std::size_t n_counter = 0; n_counter < FFT_SECTOR_SIZE; ++n_counter)
  //   {
  //     reader.SetSample(output_start + n_counter, WavReader::Channel_e::CHANNEL_TWO, input_compressed[n_counter].real());
  //   } // for
  // } // for

  reader.Write(argv[OUTPUT_PATH_ARG]);
} // main
