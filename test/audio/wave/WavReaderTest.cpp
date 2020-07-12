#include "WavReader.hpp"
#include <iostream>

#define REQUIRED_ARG_NUM 3
#define WAVEFILE_PATH_ARG 1
#define OUTPUT_PATH_ARG 2

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

  std::uint32_t differential_value = 5000;
  std::int16_t sumValue;
  for (std::uint32_t counter = 0; counter < reader.DataSize() - differential_value; ++counter)
  {
      if (counter < 100)
              std::cout << "Both: (" << reader.GetSample(counter, WavReader::Channel_e::CHANNEL_ONE) << ", " << reader.GetSample(counter+differential_value, WavReader::Channel_e::CHANNEL_ONE) << std::endl;
      sumValue = 0;
      sumValue = ((std::int32_t) reader.GetSample(counter, WavReader::Channel_e::CHANNEL_ONE)
                       +  (std::int32_t) reader.GetSample(counter+differential_value, WavReader::Channel_e::CHANNEL_ONE)) / 2.0;
      reader.SetSample(counter, WavReader::Channel_e::CHANNEL_ONE, sumValue);
      if (counter < 100)
          std::cout << "Baft: (" << reader.GetSample(counter, WavReader::Channel_e::CHANNEL_ONE) << ", " << reader.GetSample(counter+differential_value, WavReader::Channel_e::CHANNEL_ONE) << std::endl;
      sumValue = 0;
      sumValue = ((std::int32_t) reader.GetSample(counter+differential_value, WavReader::Channel_e::CHANNEL_TWO)
                       +  (std::int32_t) reader.GetSample(counter, WavReader::Channel_e::CHANNEL_TWO)) / 2.0;
      reader.SetSample(counter, WavReader::Channel_e::CHANNEL_TWO, sumValue);
  } // for

  reader.Write(argv[OUTPUT_PATH_ARG]);
} // main
