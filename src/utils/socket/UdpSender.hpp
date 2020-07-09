#ifndef UDPSENDER_HPP_
#define UDPSENDER_HPP_

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

class UdpSender
{
public:
  UdpSender(const std::string & ipAddress, int port);
  ~UdpSender();
  bool Open();
  void Close();
  bool Send(void * buffer, std::size_t size);
private:
  struct sockaddr_in servaddr_;
  int socket_fd_ {-1};
}; // UdpSender

#endif // UDPSENDER_HPP_
