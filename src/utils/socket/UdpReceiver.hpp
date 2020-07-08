#ifndef UDPRECEIVER_HPP_
#define UDPRECEIVER_HPP_


#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


class UdpReceiver
{
public:
  UdpReceiver();
  ~UdpReceiver();
  bool Open(const std::string & ipAddress, int port);
  void Close();
  ssize_t Receive(void * buffer, std::size_t size);
private:
  int socket_fd_ {-1};
}; // UdpReceiver

#endif // UDPRECEIVER_HPP_
