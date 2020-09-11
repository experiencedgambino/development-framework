#include <fstream>
#include <iostream>
#include "PCMDeviceOutput.hpp"

#define NUMBER_ARGS_REQUIRED 2

int main(int argc, char ** argv)
{
  if (argc != NUMBER_ARGS_REQUIRED)
  {
    std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
    return -1;
  } // if

  std::ifstream file_in;
  file_in.open(argv[1], std::ifstream::in | std::ifstream::binary);

  if (!file_in)
  {
    std::cout << "Failed to open file for reading" << std::endl;
    return -1;
  } // if

  PCMDeviceOutput alsa_output;
  if (alsa_output.Initialize() == false)
  {
    std::cout << "Failed to intiialize PCMDeviceOutput" << std::endl;
    return -1;
  } // if

  for (std::size_t index = 0; index < 5000; ++index)
  {
    file_in.read(alsa_output.Data(), alsa_output.Size());
    alsa_output.PlaySound();
  } // for

  return 0;
} // main
