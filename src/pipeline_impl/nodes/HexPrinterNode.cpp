#include "HexPrinterNode.hpp"

HexPrinterNode::HexPrinterNode()
{

} // HexPrinterNode

HexPrinterNode::~HexPrinterNode()
{

} // ~HexPrinterNode

void HexPrinterNode::OnDataAvailable(std::shared_ptr<PipelineData> data)
{
  std::cout << "Printing received data of size " << data->buffer_.size() << std::endl;

  for (auto & byte : data->buffer_)
  {
    std::cout << (char) byte;
  } // for
  std::cout << std::endl;
} // OnDataAvailable
