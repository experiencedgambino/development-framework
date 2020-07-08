#include "UdpReceiverNode.hpp"

UdpReceiverNode::UdpReceiverNode()
{

} // UdpReceiverNode

UdpReceiverNode::~UdpReceiverNode()
{

} // UdpReceiverNode

bool UdpReceiverNode::Initialize(const std::string & ip, int port)
{
  return receiver_.Open(ip, port);
} // Initialize

void UdpReceiverNode::OnDataAvailable(std::shared_ptr<PipelineData> data)
{
  std::cout << "Not handling data. Start node" << std::endl;
} // OnDataAvailable

void UdpReceiverNode::RunThread(void)
{
  std::vector<char> buffer(UdpReceiverNode::DEFAULT_RECEIVE_BUFFER_SIZE);
  while (IsRunning() == true)
  {
    std::size_t received_data_size = receiver_.Receive(buffer.data(), buffer.size());
    if (received_data_size >= 0)
    {
      std::shared_ptr<PipelineData> new_data = std::make_shared<PipelineData>();
      new_data->buffer_.resize(received_data_size);
      std::memcpy(new_data->buffer_.data(), buffer.data(), received_data_size);
      SendData(new_data);
    } // if

  } // while
} // RunThread
