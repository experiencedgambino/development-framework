#include "FrameDisplayNode.hpp"

FrameDisplayNode::FrameDisplayNode()
{

} // FrameDisplayNode

FrameDisplayNode::~FrameDisplayNode()
{
  // Closes all the frames
  cv::destroyAllWindows();
} // FrameDisplayNode

void FrameDisplayNode::OnDataAvailableAsync(std::shared_ptr<PipelineData> data)
{
  cv::imdecode(cv::InputArray(data->buffer_), 0, &frame);
  cv::imshow( "Frame", frame );
  if (cv::waitKey(30) > 0) std::cout << "end" << std::endl;
  SendData(data);
} // OnDataAvailableAsync
