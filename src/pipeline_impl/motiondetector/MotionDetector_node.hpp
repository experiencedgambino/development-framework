#ifndef MotionDetector_node_HPP_
#define MotionDetector_node_HPP_

#include "AsyncNode.hpp"
#include "BackgroundSubtractor.hpp"
#include "FilenameUtils.hpp"
#include "ImageTransformations.hpp"
#include "MotionDetector.hpp"

#include <chrono>
#include <opencv2/opencv.hpp>

class MotionDetector_node: public AsyncNode
{
public:
  MotionDetector_node();
  ~MotionDetector_node();

  void OnDataAvailableAsync(std::shared_ptr<PipelineData> data) override;

private:
  static const std::string DETECTIONS_DIRECTORY;
  static const int FRAME_BETWEEN_WAIT = 12;
  static const int CHANNELS_BGR = 3;

  cv::Mat frame_;
  cv::Mat flipped_;
  cv::Mat gray_frame_;
  MotionDetector motion_detector_;
  BackgroundSubtractor background_subtractor_;
  bool building_background_ {true};

  int count {0};

}; // MotionDetector_node


#endif // MotionDetector_node_HPP_
