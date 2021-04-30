#include "FrameCaptureNode_Webcam.hpp"
#include "FrameCaptureNode_Raspicam.hpp"
#include "FrameDisplayNode.hpp"
#include "MotionDetector_node.hpp"
#include "SignalUntilKill.hpp"
#include "TestMotionDetectorConfig.hpp"

#include <iostream>

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cout << argv[0] << " [config file]" << std::endl;
    return -1;
  }

  TestMotionDetectorConfig config;
  config.ReadAndParse(argv[1]);

  std::shared_ptr<Node> frame_capture_node;
  if (config.use_webcam_ == true)
  {
    frame_capture_node = std::make_shared<FrameCaptureNode_Webcam>();
  }
  else
  {
    frame_capture_node = std::make_shared<FrameCaptureNode_Raspicam>();
  }

  std::shared_ptr<Node> motion_detector_node = std::make_shared<MotionDetector_node>();

  if (config.use_webcam_ == true)
  {
    std::dynamic_pointer_cast<FrameCaptureNode_Webcam>(frame_capture_node)->Initialize();
  }
  else
  {
    std::dynamic_pointer_cast<FrameCaptureNode_Raspicam>(frame_capture_node)->Initialize();
  }

  frame_capture_node->RegisterNodeAsNext(motion_detector_node);

  std::dynamic_pointer_cast<MotionDetector_node>(motion_detector_node)->Run();
  if (config.use_webcam_ == true)
  {
    std::dynamic_pointer_cast<FrameCaptureNode_Webcam>(frame_capture_node)->Run();
  }
  else
  {
    std::dynamic_pointer_cast<FrameCaptureNode_Raspicam>(frame_capture_node)->Run();
  }

  SignalUntilKill suk;
  suk.ReturnOnSignal();
} // main
