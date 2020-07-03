#ifndef RECEPTOR_HPP
#define RECEPTOR_HPP

#include <memory>
#include "MessageQueue.hpp"
#include "PipelineData.hpp"

class Receptor
{
public:
  virtual void ReceiveData(std::shared_ptr<PipelineData> data);
  
}; // Receptor

#endif // RECEPTOR_HPP
