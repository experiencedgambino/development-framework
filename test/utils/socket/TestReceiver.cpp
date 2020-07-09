#include "StringConverter.hpp"
#include "UdpReceiver.hpp"

#define NUM_COMMAND_LINE_ARGS 4
#define IP_ARGNUM 1
#define PORT_ARGNUM 2
#define SIZE_ARGNUM 3

int main(int argc, char ** argv)
{
  if (argc != NUM_COMMAND_LINE_ARGS)
  {
    std::cout << "Usage: TestSender [IP] [PORT] [RECEIVE_SIZE_BYTES]" << std::endl;
    return -1;
  } // if

  UdpReceiver receiver;

  int port = StringConverter::StringTo<int>(argv[PORT_ARGNUM]);

  receiver.Open(argv[IP_ARGNUM], port);
  std::size_t size_to_alloc = StringConverter::StringTo<std::size_t>(argv[SIZE_ARGNUM]);;
  char * buffer = (char *) malloc(size_to_alloc);
  while (true)
  {
    std::cout << receiver.Receive(buffer, size_to_alloc) << std::endl;
  } // while
} // main
