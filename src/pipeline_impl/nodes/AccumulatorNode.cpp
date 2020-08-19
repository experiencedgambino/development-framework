#include "AccumulatorNode.hpp"

AccumulatorNode::AccumulatorNode(std::size_t chunkSizeBytes):
  sizeToAccumulate_(chunkSizeBytes),
  bufferToSend_(std::make_shared<PipelineData>(chunkSizeBytes))
{

} // AccumulatorNode

AccumulatorNode::~AccumulatorNode()
{

} // ~AccumulatorNode

void AccumulatorNode::OnDataAvailable(std::shared_ptr<PipelineData> data)
{
  if (data->buffer_.size() + totalSize_ < sizeToAccumulate_)
  {
    std::memcpy(bufferToSend_->buffer_.data()+totalSize_, data->buffer_.data(), data->buffer_.size());
    totalSize_ += data->buffer_.size();
  } // if
  else
  {
    std::size_t portion_of_buffer_to_first_copy = sizeToAccumulate_ - totalSize_;

    // First copy, will involve currently saved buffer
    std::memcpy(bufferToSend_->buffer_.data()+totalSize_, data->buffer_.data(), portion_of_buffer_to_first_copy);
    SendData(bufferToSend_);
    bufferToSend_ = std::make_shared<PipelineData>(sizeToAccumulate_);

    std::size_t current_buffer_byte_index = portion_of_buffer_to_first_copy;

    if (data->buffer_.size() > sizeToAccumulate_)
    {
      for (;current_buffer_byte_index <= data->buffer_.size() - sizeToAccumulate_; current_buffer_byte_index += sizeToAccumulate_)
      {
        std::memcpy(bufferToSend_->buffer_.data(), data->buffer_.data()+current_buffer_byte_index, sizeToAccumulate_);
        SendData(bufferToSend_);
        bufferToSend_ = std::make_shared<PipelineData>(sizeToAccumulate_);
      } // while
    } // if

    std::int32_t remaining_bytes = data->buffer_.size() - current_buffer_byte_index;
    if (remaining_bytes > 0)
    {
      std::memcpy(bufferToSend_->buffer_.data(), data->buffer_.data()+current_buffer_byte_index, remaining_bytes);
      totalSize_ = remaining_bytes;
    } // if

  } // else
} // OnDataAvailable
