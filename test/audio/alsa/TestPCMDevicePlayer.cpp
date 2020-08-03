#include <iostream>
#include "PCMDevicePlayer.hpp"

int main(int argc, char ** argv)
{
  PCMDevicePlayer player;
  if (player.Initialize() == false)
  {
    std::cout << "Failed to intiialize PCMDevicePlayer" << std::endl;
    return -1;
  } // if

  for (std::size_t index = 0; index < 5000; ++index)
  {
    std::cout << index << std::endl;
    player.ReadSound();
  } // for
} // main
