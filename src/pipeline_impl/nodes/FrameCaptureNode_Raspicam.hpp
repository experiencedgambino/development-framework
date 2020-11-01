#ifndef FRAMECAPTURENODE_RASPICAM_HPP
#define FRAMECAPTURENODE_RASPICAM_HPP

#include <cstring>
#include <iostream>

#include "AbstractThread.hpp"
#include "Node.hpp"
#include "OpenCV_Raspicam.hpp"

class FrameCaptureNode_Raspicam: public Node, public AbstractThread
{
public:
  FrameCaptureNode_Raspicam();
  ~FrameCaptureNode_Raspicam();

  void OnDataAvailable(std::shared_ptr<PipelineData> data) override;
  bool Initialize();

protected:
  void RunThread(void) override;


private:
  OpenCV_Raspicam webcam_{};
}; // UdpReceiverNode

#endif // FRAMECAPTURENODE_RASPICAM_HPP
