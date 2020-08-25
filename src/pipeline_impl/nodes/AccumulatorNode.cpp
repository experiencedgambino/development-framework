#include "AccumulatorNode.hpp"

AccumulatorNode::AccumulatorNode(std::size_t chunkSizeBytes):
  sizeToAccumulate_(chunkSizeBytes),
  bufferToSend_(std::make_shared<PipelineData>(sizeToAccumulate_))
{

} // AccumulatorNode

AccumulatorNode::~AccumulatorNode()
{

} // ~AccumulatorNode

void AccumulatorNode::OnDataAvailable(std::shared_ptr<PipelineData> data)
{
  std::size_t current_buffer_byte_index = 0;
  std::size_t number_bytes_remaining = data->buffer_.size();

  while (current_buffer_byte_index < data->buffer_.size())
  {
    std::size_t number_of_bytes_to_copy = std::min(number_bytes_remaining, sizeToAccumulate_ - totalSize_);

    std::memcpy(bufferToSend_->buffer_.data()+totalSize_, data->buffer_.data()+current_buffer_byte_index, number_of_bytes_to_copy);
    current_buffer_byte_index += number_of_bytes_to_copy;
    totalSize_ += number_of_bytes_to_copy;
    number_bytes_remaining -= number_of_bytes_to_copy;

    // check if ready to send
    if (totalSize_ == sizeToAccumulate_)
    {
      totalSize_ = 0;
      SendData(bufferToSend_);
      bufferToSend_ = std::make_shared<PipelineData>(sizeToAccumulate_);
    } // if
  } // while

  if (number_bytes_remaining > 0)
  {
    std::size_t starting_index_remaining = data->buffer_.size() - number_bytes_remaining;

    std::memcpy(bufferToSend_->buffer_.data(), data->buffer_.data()+starting_index_remaining, number_bytes_remaining);
    totalSize_ = number_bytes_remaining;
  } // if
} // OnDataAvailable
