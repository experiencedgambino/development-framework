#include "CooleyTurkeyFFT.hpp"
#include "WavReader.hpp"

#include <complex>
#include <iostream>

#define REQUIRED_ARG_NUM 3
#define WAVEFILE_PATH_ARG 1
#define OUTPUT_PATH_ARG 2

#define FFT_SECTOR_SIZE 4096
#define NUM_MINS_TO_ELIMINATE 4000

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

  // std::uint32_t differential_value = 0;
  // std::int16_t sumValue;
  // for (std::uint32_t counter = 0; counter < reader.DataSize() - differential_value; ++counter)
  // {
  //     sumValue = 0;
  //     sumValue = ((std::int32_t) reader.GetSample(counter, WavReader::Channel_e::CHANNEL_ONE)
  //                      +  (std::int32_t) reader.GetSample(counter+differential_value, WavReader::Channel_e::CHANNEL_ONE)) / 2.0;
  //     reader.SetSample(counter, WavReader::Channel_e::CHANNEL_ONE, sumValue);
  //     sumValue = 0;
  //     sumValue = ((std::int32_t) reader.GetSample(counter+differential_value, WavReader::Channel_e::CHANNEL_TWO)
  //                      +  (std::int32_t) reader.GetSample(counter, WavReader::Channel_e::CHANNEL_TWO)) / 2.0;
  //     reader.SetSample(counter, WavReader::Channel_e::CHANNEL_TWO, sumValue);
  // } // for

  // Convert arrays to double
  double * channel_one_double_array = (double *) malloc(reader.DataSize() * sizeof(double));
  double * channel_two_double_array = (double *) malloc(reader.DataSize() * sizeof(double));
  for (std::size_t counter = 0; counter < reader.DataSize(); ++counter)
  {
    // std::cout << counter << std::endl;
    channel_one_double_array[counter] = reader.GetSample(counter, WavReader::Channel_e::CHANNEL_ONE);
    channel_two_double_array[counter] = reader.GetSample(counter, WavReader::Channel_e::CHANNEL_TWO);
  } // for
  //
  // Take the FFT of each sector of specified size
  std::complex<double> * output = (std::complex<double> *) malloc(FFT_SECTOR_SIZE * sizeof(std::complex<double>));
  std::complex<double> * input_compressed = (std::complex<double> *) malloc(FFT_SECTOR_SIZE * sizeof(std::complex<double>));
  double * magnitude_output = (double *) malloc(FFT_SECTOR_SIZE * sizeof(double));
  for (std::size_t sector_counter = 0; sector_counter < reader.DataSize() / FFT_SECTOR_SIZE; ++sector_counter)
  {
    // CHANNEL 1 calculations
    if (fft(channel_one_double_array+(FFT_SECTOR_SIZE * sector_counter), output, FFT_SECTOR_SIZE) == false)
    {
      std::cout << "Cannot take FFT chan 1" << std::endl;
    } // if
    for (std::size_t k_counter = 0; k_counter < FFT_SECTOR_SIZE; ++k_counter)
    {
      magnitude_output[k_counter] = std::abs(output[k_counter]);
    } // for
    for (std::size_t min_counter = 0; min_counter < NUM_MINS_TO_ELIMINATE; ++min_counter)
    {
      std::size_t minimum_output = std::min_element(magnitude_output, magnitude_output+FFT_SECTOR_SIZE) - magnitude_output;
      magnitude_output[minimum_output] = 100000000.0;
      output[minimum_output] = std::complex<double>(0,0);
    } // for
    idft_attempt(output, input_compressed, FFT_SECTOR_SIZE, 1);
    for(std::size_t n_counter = 0; n_counter < FFT_SECTOR_SIZE; ++n_counter)
    {
      reader.SetSample((FFT_SECTOR_SIZE * sector_counter) + n_counter, WavReader::Channel_e::CHANNEL_ONE, std::abs(input_compressed[n_counter]));
    } // for


    // CHANNEL 2 calculations
    if (fft(channel_two_double_array+(FFT_SECTOR_SIZE * sector_counter), output, FFT_SECTOR_SIZE) == false)
    {
      std::cout << "Cannot take FFT chan 2" << std::endl;
    } // if
    for (std::size_t k_counter = 0; k_counter < FFT_SECTOR_SIZE; ++k_counter)
    {
      magnitude_output[k_counter] = std::abs(output[k_counter]);
    } // for
    for (std::size_t min_counter = 0; min_counter < NUM_MINS_TO_ELIMINATE; ++min_counter)
    {
      std::size_t minimum_output = std::min_element(magnitude_output, magnitude_output+FFT_SECTOR_SIZE) - magnitude_output;
      magnitude_output[minimum_output] = 100000000.0;
      output[minimum_output] = std::complex<double>(0,0);
    } // for

    idft_attempt(output, input_compressed, FFT_SECTOR_SIZE, 1);

    for(std::size_t n_counter = 0; n_counter < FFT_SECTOR_SIZE; ++n_counter)
    {
      reader.SetSample((FFT_SECTOR_SIZE * sector_counter) + n_counter, WavReader::Channel_e::CHANNEL_TWO, std::abs(input_compressed[n_counter]));
    } // for

  } // for
  //


  //
  //
  // for (std::size_t counter = 0; counter < reader.DataSize(); ++counter)
  // {
  //   channel_one_double_array[counter] = reader.GetSample(counter, WavReader::Channel_e::CHANNEL_ONE);
  //   channel_two_double_array[counter] = reader.GetSample(counter, WavReader::Channel_e::CHANNEL_TWO);
  // } // for


  reader.Write(argv[OUTPUT_PATH_ARG]);
} // main
