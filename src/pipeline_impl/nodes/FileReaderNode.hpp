#ifndef FILERECORDERNODE_C_HPP
#define FILERECORDERNODE_C_HPP

#include <cstring>
#include <fstream>
#include <iostream>

#include "AbstractThread.hpp"
#include "Node.hpp"

class FileReaderNode: public Node, public AbstractThread
{
public:
  FileReaderNode();
  ~FileReaderNode();
  bool Initialize(const std::string & filename, std::size_t batchSize = DEFAULT_BATCH_SIZE);

  void OnDataAvailable(std::shared_ptr<PipelineData> data) override;


protected:
  void RunThread(void) override;

private:
  static const std::size_t DEFAULT_BATCH_SIZE = 1024;

  std::ifstream inputFileStream_;
  std::size_t batchSize_ {DEFAULT_BATCH_SIZE};
}; // FileReaderNode

#endif // FILERECORDERNODE_C_HPP
