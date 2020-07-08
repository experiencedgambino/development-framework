#ifndef HEXPRINTERNODE_HPP_
#define HEXPRINTERNODE_HPP_

#include <iostream>
#include "AbstractThread.hpp"
#include "Node.hpp"
#include "UdpReceiver.hpp"

class HexPrinterNode: public Node
{
public:
  HexPrinterNode();
  ~HexPrinterNode();

  void OnDataAvailable(std::shared_ptr<PipelineData> data) override;

}; // HexPrinterNode

#endif // HEXPRINTERNODE_HPP_
