#include <fstream>
#include <iostream>
#include "PCMDevicePlayer.hpp"

#define NUMBER_ARGS_REQUIRED 2

int main(int argc, char ** argv)
{
  if (argc != NUMBER_ARGS_REQUIRED)
  {
    std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
    return -1;
  } // if

  std::ofstream file_out;
  file_out.open(argv[1], std::ofstream::out | std::ofstream::binary);

  if (!file_out)
  {
    std::cout << "Failed to open file for writing" << std::endl;
    return -1;
  } // if

  PCMDevicePlayer alsa_input;
  if (alsa_input.Initialize() == false)
  {
    std::cout << "Failed to intiialize PCMDevicePlayer" << std::endl;
    return -1;
  } // if

  for (std::size_t index = 0; index < 5000; ++index)
  {
    alsa_input.ReadSound();
    file_out.write(alsa_input.Data(), alsa_input.Size());
  } // for

  return 0;
} // main
