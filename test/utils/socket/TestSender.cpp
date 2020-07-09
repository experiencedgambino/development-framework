#include "StringConverter.hpp"
#include "UdpSender.hpp"

#include <cstring>
#include <vector>

#define NUM_COMMAND_LINE_ARGS 5
#define IP_ARGNUM 1
#define PORT_ARGNUM 2
#define SIZE_ARGNUM 3
#define SENDS_COUNT_ARGNUM 4

static const std::string TO_POPULATE = "TestStringToSend";

void PopulateBuffer(std::vector<char> & buffer)
{
  std::size_t rounded_size = buffer.size() / TO_POPULATE.size();
  for (std::size_t counter = 0; counter < rounded_size; ++counter)
  {
    std::memcpy(buffer.data()+(counter*TO_POPULATE.size()), TO_POPULATE.c_str(), TO_POPULATE.size());
  } // for
} // PopulateBuffer

int main(int argc, char ** argv)
{
  if (argc != NUM_COMMAND_LINE_ARGS)
  {
    std::cout << "Usage: TestSender [IP] [PORT] [Size (bytes] [Number of sends]" << std::endl;
    return -1;
  } // if

  // Parse command line args (if needed)
  int port = StringConverter::StringTo<int>(argv[PORT_ARGNUM]);
  int size_bytes = StringConverter::StringTo<int>(argv[SIZE_ARGNUM]);
  int number_of_sends = StringConverter::StringTo<int>(argv[SENDS_COUNT_ARGNUM]);

  // Create sender
  UdpSender sender(argv[IP_ARGNUM], port);
  if (sender.Open() == false)
  {
    std::cout << "Failed to open UDP sender socket" << std::endl;
    return -1;
  } // if

  // Create buffer
  std::vector<char> buffer (size_bytes);

  // Populate buffer
  PopulateBuffer(buffer);

  // send data
  for (int counter = 0; counter < number_of_sends; ++counter)
  {
    std::cout << "Sending UDP packet " << counter+1 << " of size " << size_bytes << std::endl;
    if (sender.Send(buffer.data(), buffer.size()) == false)
    {
      std::cout << "Failed to send" << std::endl;
    } // if
  } // for

  sender.Close();
} // main
