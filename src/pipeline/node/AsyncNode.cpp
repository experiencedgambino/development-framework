
#include "AsyncNode.hpp"

AsyncNode::~AsyncNode()
{
  DetachStop();
  while (thread_finished_ == false)
  {
    message_queue_.Enqueue(nullptr);
  } // while
}

void AsyncNode::OnDataAvailable(std::shared_ptr<PipelineData> data)
{
  message_queue_.Enqueue(data);
} // OnDataAvailable

void AsyncNode::RunThread(void)
{
  thread_finished_ = false;
  while (IsRunning() == true)
  {
    std::shared_ptr<PipelineData> new_data = message_queue_.WaitDequeue();
    if (new_data != nullptr)
    {
      OnDataAvailableAsync(new_data);
    } // if
    else
    {
      // Continue
    }
  } // while

  thread_finished_ = true;
} // RunThread
