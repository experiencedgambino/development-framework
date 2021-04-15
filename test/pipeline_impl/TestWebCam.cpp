#include "FrameCaptureNode_Webcam.hpp"
#include "FrameDisplayNode.hpp"
#include "SignalUntilKill.hpp"

#include <iostream>

int main()
{
  std::shared_ptr<Node> frame_capture_node = std::make_shared<FrameCaptureNode_Webcam>();
  std::shared_ptr<Node> frame_display_node = std::make_shared<FrameDisplayNode>();
  std::dynamic_pointer_cast<FrameCaptureNode_Webcam>(frame_capture_node)->Initialize();

  frame_capture_node->RegisterNodeAsNext(frame_display_node);

  std::dynamic_pointer_cast<FrameDisplayNode>(frame_display_node)->Run();
  std::dynamic_pointer_cast<FrameCaptureNode_Webcam>(frame_capture_node)->Run();

  SignalUntilKill suk;
  suk.ReturnOnSignal();
} // main
