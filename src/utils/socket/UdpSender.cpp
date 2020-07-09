#include "UdpSender.hpp"

UdpSender::UdpSender(const std::string & ipAddress, int port)
{
  // Filling server information
  servaddr_.sin_family = AF_INET;
  servaddr_.sin_port = htons( port );
  servaddr_.sin_addr.s_addr = inet_addr(ipAddress.c_str());;
} // UdpSender

UdpSender::~UdpSender()
{
  Close();
} // UdpSender

bool UdpSender::Open()
{
  bool ret {true};
  socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0);

  if (socket_fd_ == -1)
  {
    std::cerr << "UdpSender: ERROR: Unable to create socket" << std::endl;
    ret = false;
  } // if

  return ret;
} // Open

bool UdpSender::Send(void * buffer, std::size_t size)
{
  ssize_t send_size = sendto(socket_fd_, buffer, size, MSG_DONTWAIT, (struct sockaddr *)&servaddr_, sizeof(servaddr_));
  if (send_size != size)
  {
    return false;
  } // if
  return true;
} // Receive

void UdpSender::Close()
{
  close(socket_fd_);
} // Close
