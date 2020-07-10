#ifndef PIPELINEDATA_HPP_
#define PIPELINEDATA_HPP_

#include <cstdint>
#include <vector>

class PipelineData
{
public:
  ~PipelineData();
  PipelineData & operator=(const PipelineData & data);

  std::vector<std::uint8_t> buffer_ {};
}; // PipelineData

#endif // PIPELINEDATA_HPP_
