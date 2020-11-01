#include "MotionDetector_node.hpp"

const std::string MotionDetector_node::DETECTIONS_DIRECTORY = "detections";

MotionDetector_node::MotionDetector_node()
{
  std::filesystem::create_directories(MotionDetector_node::DETECTIONS_DIRECTORY);
}
MotionDetector_node::~MotionDetector_node()
{

} // MotionDetector_node

std::string type2str(int type) {
  std::string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}

void MotionDetector_node::OnDataAvailableAsync(std::shared_ptr<PipelineData> data)
{
  count = (count + 1) % 5;

  if (count == 4)
  {
    cv::imdecode(cv::InputArray(data->buffer_), 0, &frame_);

    ImageTransformations::NormalizeImage(frame_);


    if (building_background_ == true)
    {
      background_subtractor_.resetBackground(frame_);
      building_background_ = false;
    } // if

    bool motion_detected = motion_detector_.detect(frame_, background_subtractor_.getBackground());
    if (motion_detected)
    {
      std::time_t timestamp = std::time(nullptr);
      cv::imwrite(MotionDetector_node::DETECTIONS_DIRECTORY + "/" + std::to_string(timestamp) + ".jpg", frame_);
    } // if

    // Note decrease frequency of frame addition
    background_subtractor_.addFrame(frame_, .1); // Add a frame to the background subtractor

  } // if

  // // Assumes image is greyscale at this point

} // OnDataAvailableAsync
