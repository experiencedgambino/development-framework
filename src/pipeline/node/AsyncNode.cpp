#include "AsyncNode.hpp"

void AsyncNode::OnDataAvailable(std::shared_ptr<PipelineData> data)
{
  message_queue_.Enqueue(data);
} // OnDataAvailable

void AsyncNode::RunThread(void)
{
  while (IsRunning() == true)
  {
    std::shared_ptr<PipelineData> new_data = message_queue_.WaitDequeue();
    if (new_data != nullptr)
    {
      OnDataAvailableAsync(new_data);
    } // if
  } // while
} // RunThread
