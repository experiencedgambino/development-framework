#ifndef FRAMEDISPLAYNODE_HPP_
#define FRAMEDISPLAYNODE_HPP_

#include "AsyncNode.hpp"
#include "opencv2/opencv.hpp"

class FrameDisplayNode: public AsyncNode
{
public:
  FrameDisplayNode();
  ~FrameDisplayNode();

  void OnDataAvailableAsync(std::shared_ptr<PipelineData> data) override;

private:
  cv::Mat frame;

}; // FRAMEDISPLAYNODE_HPP_



#endif // FRAMEDISPLAYNODE_HPP_
