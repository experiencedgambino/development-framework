#include "FrameCaptureNode_Raspicam.hpp"

FrameCaptureNode_Raspicam::FrameCaptureNode_Raspicam()
{

} // FrameCaptureNode_Raspicam

FrameCaptureNode_Raspicam::~FrameCaptureNode_Raspicam()
{

} // FrameCaptureNode_Raspicam

void FrameCaptureNode_Raspicam::OnDataAvailable(std::shared_ptr<PipelineData> data)
{
  std::cout << "Not handling data. Start node" << std::endl;
} // OnDataAvailable

bool FrameCaptureNode_Raspicam::Initialize()
{
  return webcam_.open();
} // Initialize

void FrameCaptureNode_Raspicam::RunThread(void)
{
  cv::Mat current_frame;
  std::vector<std::uint8_t> buffer;
  std::shared_ptr<PipelineData> current_pipeline_data;
  while (IsRunning() == true)
  {
    current_pipeline_data = std::make_shared<PipelineData>();
    webcam_.getFrame(current_frame);
    cv::imencode(".jpg", current_frame, current_pipeline_data->buffer_);
    SendData(current_pipeline_data);
  } // while
} // RunThread
