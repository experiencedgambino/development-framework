#include "UdpReceiver.hpp"

int main(int argc, char ** argv)
{
  UdpReceiver receiver;

  receiver.Open("127.0.0.1", 19000);
  std::size_t size_to_alloc = 50000;
  char * buffer = (char *) malloc(size_to_alloc);
  while (true)
  {
    std::cout << receiver.Receive(buffer, size_to_alloc) << std::endl;
  } // while
} // main
