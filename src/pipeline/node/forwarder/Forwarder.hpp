#ifndef FORWARDER_HPP
#define FORWARDER_HPP

#include <memory>

#include "PipelineData.hpp"
#include "Receptor.hpp"

class Forwarder
{
public:
  virtual void ForwardData(std::shared_ptr<PipelineData> data) = 0;
  virtual void ForwardToNode(std::shared_ptr<Receptor> receptor) = 0;
}; // Forwarder

#endif // FORWARDER_HPP
