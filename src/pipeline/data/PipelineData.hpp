#ifndef PIPELINEDATA_HPP_
#define PIPELINEDATA_HPP_

#include <cstdint>
#include <vector>

class PipelineData
{
public:
  std::vector<std::uint8_t> buffer_ {};

  PipelineData & operator=(const PipelineData & data);

}; // PipelineData

#endif // PIPELINEDATA_HPP_
