#ifndef PCMDEVICEPLAYERNODE_HPP_
#define PCMDEVICEPLAYERNODE_HPP_

#include <cstring>
#include <iostream>
#include "AbstractThread.hpp"
#include "Node.hpp"
#include "PCMDevicePlayer.hpp"

class PCMDevicePlayerNode: public Node, public AbstractThread
{
public:
  PCMDevicePlayerNode();
  ~PCMDevicePlayerNode();
  bool Initialize(void);

  void OnDataAvailable(std::shared_ptr<PipelineData> data) override;


protected:
  void RunThread(void) override;

private:
  PCMDevicePlayer player;
}; // UdpReceiverNode

#endif // PCMDevicePlayerNode
