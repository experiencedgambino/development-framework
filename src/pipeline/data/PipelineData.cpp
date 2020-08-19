#include "PipelineData.hpp"

PipelineData::PipelineData()
{

} // PipelineData

PipelineData::PipelineData(std::size_t allocatedsize)
{
  buffer_.resize(allocatedsize);
} // PipelineData

PipelineData::~PipelineData()
{

} // PipelineData

PipelineData & PipelineData::operator=(const PipelineData & data)
{
  buffer_ = data.buffer_;
  return *this;
} // PipelineData
