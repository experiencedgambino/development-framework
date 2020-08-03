#ifndef FILERECORDERNODE_HPP_
#define FILERECORDERNODE_HPP_

#include <fstream>

#include "AsyncNode.hpp"

class FileRecorderNode: public AsyncNode
{
public:
  FileRecorderNode();
  ~FileRecorderNode();

  bool Initialize(const std::string & filename);
  void OnDataAvailableAsync(std::shared_ptr<PipelineData> data) override;

private:
  std::ofstream outputstream_ {};
}; // FileRecorderNode


#endif // FILERECORDERNODE_HPP_
