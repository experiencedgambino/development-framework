#ifndef MotionDetector_node_HPP_
#define MotionDetector_node_HPP_

#include "AsyncNode.hpp"
#include "MotionDetector.hpp"
#include "BackgroundSubtractor.hpp"
#include <opencv2/opencv.hpp>

class MotionDetector_node: public AsyncNode
{
public:
  MotionDetector_node();
  ~MotionDetector_node();

  void OnDataAvailableAsync(std::shared_ptr<PipelineData> data) override;

private:
  cv::Mat frame_;
  cv::Mat gray_frame_;
  MotionDetector motion_detector_;
  BackgroundSubtractor background_subtractor_;
  bool building_background_ {true};

}; // MotionDetector_node


#endif // MotionDetector_node_HPP_
