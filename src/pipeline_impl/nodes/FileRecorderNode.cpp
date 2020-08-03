#include "FileRecorderNode.hpp"

FileRecorderNode::FileRecorderNode()
{

}
FileRecorderNode::~FileRecorderNode()
{
  outputstream_.close();
} // FileRecorderNode

bool FileRecorderNode::Initialize(const std::string & filename)
{
  outputstream_.open (filename, std::ios::binary | std::ios::out);
} // Initialize

void FileRecorderNode::OnDataAvailableAsync(std::shared_ptr<PipelineData> data)
{
  outputstream_.write((char *)data->buffer_.data(), data->buffer_.size());
} // OnDataAvailableAsync
