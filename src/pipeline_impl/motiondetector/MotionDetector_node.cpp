#include "MotionDetector_node.hpp"

MotionDetector_node::MotionDetector_node()
{

}
MotionDetector_node::~MotionDetector_node()
{

} // MotionDetector_node

void MotionDetector_node::OnDataAvailableAsync(std::shared_ptr<PipelineData> data)
{
  cv::imdecode(cv::InputArray(data->buffer_), 0, &frame_);

  // Assumes image is greyscale at this point

  if (building_background_ == true)
  {
    background_subtractor_.resetBackground(frame_);
    building_background_ = false;
  } // if

  bool motion_detected = motion_detector_.detect(frame_, background_subtractor_.getBackground());
  if (motion_detected)
  {
    std::time_t timestamp = std::time(nullptr);
    std::cout << timestamp << std::endl;
  } // if

  // Note decrease frequency of frame addition
  background_subtractor_.addFrame(frame_, .1); // Add a frame to the background subtractor
} // OnDataAvailableAsync
