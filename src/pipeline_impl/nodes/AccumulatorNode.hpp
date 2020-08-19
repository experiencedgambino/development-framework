#ifndef ACCUMULATORNODE_HPP_
#define ACCUMULATORNODE_HPP_

#include "Node.hpp"

#include <cstring>

class AccumulatorNode: public Node
{
public:
  AccumulatorNode(std::size_t chunkSizeBytes);
  ~AccumulatorNode();

  void OnDataAvailable(std::shared_ptr<PipelineData> data) override;

private:
  // current total size stored in queue
  std::size_t totalSize_ {0};

  // current accumulated size
  std::size_t sizeToAccumulate_;

  // storage for data that isn't ready yet
  std::shared_ptr<PipelineData> bufferToSend_;

}; // AccumulatorNode

#endif // ACCUMULATORNODE_HPP_
