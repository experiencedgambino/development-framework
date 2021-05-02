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
  counter_ = (counter_ + 1) % FRAME_DISPLAY_SKIP_COUNT;
  if (counter_ == 0)
  {
    cv::imdecode(cv::InputArray(data->buffer_), cv::IMREAD_COLOR, &frame);
    cv::imshow( "Frame", frame );
    if (cv::waitKey(30) > 0) std::cout << "end" << std::endl;
    SendData(data);
  } // if
} // OnDataAvailableAsync
