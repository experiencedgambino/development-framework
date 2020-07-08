#ifndef HEXPRINTERNODE_HPP_
#define HEXPRINTERNODE_HPP_

#include <iostream>
#include "AbstractThread.hpp"
#include "AsyncNode.hpp"
#include "UdpReceiver.hpp"

class HexPrinterNode: public AsyncNode
{
public:
  HexPrinterNode();
  ~HexPrinterNode();

  void OnDataAvailableAsync(std::shared_ptr<PipelineData> data) override;

}; // HexPrinterNode

#endif // HEXPRINTERNODE_HPP_
