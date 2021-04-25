#include "FrameCaptureNode_Webcam.hpp"
#include "FrameCaptureNode_Raspicam.hpp"
#include "FrameDisplayNode.hpp"
#include "SignalUntilKill.hpp"
#include "FileReaderUtils_c.hpp"
#include "rapidjson/document.h"
#include <iostream>

class TestWebCamConfig
{
public:
  TestWebCamConfig()
  {

  }

  void ReadAndParse(const std::string & configPath)
  {
    std::string str;
    OpenFileAndReadIntoString(configPath, str);

    rapidjson::Document document;
    document.Parse(str.c_str());
    assert(document.HasMember("webcam"));

    use_webcam_ = document["webcam"].GetBool();

  }; // ReadAndParse

  bool use_webcam_ {false};
}; // TestWebCamConfig



int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cout << argv[0] << " [config file]" << std::endl;
    return -1;
  }

  TestWebCamConfig config;
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

  std::shared_ptr<Node> frame_display_node = std::make_shared<FrameDisplayNode>();

  if (config.use_webcam_ == true)
  {
    std::dynamic_pointer_cast<FrameCaptureNode_Webcam>(frame_capture_node)->Initialize();
  }
  else
  {
    std::dynamic_pointer_cast<FrameCaptureNode_Raspicam>(frame_capture_node)->Initialize();
  }

  frame_capture_node->RegisterNodeAsNext(frame_display_node);

  std::dynamic_pointer_cast<FrameDisplayNode>(frame_display_node)->Run();

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
