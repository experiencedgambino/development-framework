#include "PCMDevicePlayerNode.hpp"

PCMDevicePlayerNode::PCMDevicePlayerNode()
{

} // PCMDevicePlayerNode

PCMDevicePlayerNode::~PCMDevicePlayerNode()
{
  Stop();
  player.Shutdown();
} // PCMDevicePlayerNode

bool PCMDevicePlayerNode::Initialize()
{
  return player.Initialize();
} // Initialize

void PCMDevicePlayerNode::OnDataAvailable(std::shared_ptr<PipelineData> data)
{
  std::cout << "Not handling data. Start node" << std::endl;
} // OnDataAvailable

void PCMDevicePlayerNode::RunThread(void)
{
  const char * databuffer = player.Data();
  std::size_t buffersize_ = player.Size();
  while (IsRunning() == true)
  {
    player.ReadSound();

    std::shared_ptr<PipelineData> new_data = std::make_shared<PipelineData>();
    new_data->buffer_.resize(buffersize_);
    std::memcpy(new_data->buffer_.data(), databuffer, buffersize_);
    SendData(new_data);
  } // while
} // RunThread
