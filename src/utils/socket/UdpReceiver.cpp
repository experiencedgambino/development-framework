#include "UdpReceiver.hpp"

UdpReceiver::UdpReceiver()
{

} // UdpReceiver

bool UdpReceiver::Open(const std::string & ipAddress, int port)
{
  bool ret {true};
  socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0);

  // address struct used for binding
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(ipAddress.c_str());
  address.sin_port = htons( port );

  if (socket_fd_ == -1)
  {
    std::cerr << "UdpReceiver: ERROR: Unable to create socket" << std::endl;
    ret = false;
  } // if

  if (bind(socket_fd_, (struct sockaddr *)&address, sizeof(address)) == -1)
  {
    std::cerr << "UdpReceiver: ERROR: Unable to bind socket" << std::endl;
    ret = false;
  } // if

  return ret;
} // Open

ssize_t UdpReceiver::Receive(void * buffer, std::size_t size)
{
  ssize_t receive_size = recv(socket_fd_, buffer, size, 0);
  return receive_size;
} // Receive

void UdpReceiver::Close()
{
  close(socket_fd_);
} // Close
