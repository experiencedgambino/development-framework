#ifndef FRAMECAPTURENODE_WEBCAM_HPP
#define FRAMECAPTURENODE_WEBCAM_HPP

#include <cstring>
#include <iostream>

#include "AbstractThread.hpp"
#include "Node.hpp"
#include "OpenCV_WebCam.hpp"
#include <opencv2/imgcodecs.hpp>

class FrameCaptureNode_Webcam: public Node, public AbstractThread
{
public:
  FrameCaptureNode_Webcam();
  ~FrameCaptureNode_Webcam();

  void OnDataAvailable(std::shared_ptr<PipelineData> data) override;
  bool Initialize();

protected:
  void RunThread(void) override;


private:
  OpenCV_WebCam webcam_{};
}; // UdpReceiverNode

#endif // FRAMECAPTURENODE_WEBCAM_HPP
