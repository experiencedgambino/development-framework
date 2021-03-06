#ifndef GENERICFORWARDER_HPP
#define GENERICFORWARDER_HPP

#include <algorithm>
#include <vector>
#include "Forwarder.hpp"

class GenericForwarder: public Forwarder
{
public:
  void ForwardData(std::shared_ptr<PipelineData> data) final;
  void ForwardToNode(std::shared_ptr<Receptor> receptor) final;

  std::vector<std::shared_ptr<Receptor>> receptor_list_ {};
  std::size_t index_ {0};
}; // Forwarder

#endif // GENERICFORWARDER_HPP
