#include "PipelineData.hpp"

PipelineData & PipelineData::operator=(const PipelineData & data)
{
  buffer_ = data.buffer_;
  return *this;
} // PipelineData