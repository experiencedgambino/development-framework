#ifndef UDPRECEIVERNORE_HPP_
#define UDPRECEIVERNORE_HPP_

#include <cstring>
#include <iostream>
#include "AbstractThread.hpp"
#include "Node.hpp"
#include "UdpReceiver.hpp"

class UdpReceiverNode: public Node, public AbstractThread
{
public:
  UdpReceiverNode();
  ~UdpReceiverNode();
  bool Initialize(const std::string & ip, int port);

  void OnDataAvailable(std::shared_ptr<PipelineData> data) override;


protected:
  void RunThread(void) override;

private:
  static const std::size_t DEFAULT_RECEIVE_BUFFER_SIZE = 50000;

  UdpReceiver receiver_;
}; // UdpReceiverNode

#endif // UDPRECEIVERNORE_HPP_
