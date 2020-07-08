#ifndef NODE_HPP_
#define NODE_HPP_

#include <memory>
#include "Forwarder.hpp"
#include "GenericForwarder.hpp"
#include "PipelineData.hpp"

class Node: public Receptor
{
public:
  Node(std::shared_ptr<Forwarder> forwarder = std::make_shared<GenericForwarder>());

  virtual void OnDataAvailable(std::shared_ptr<PipelineData> data) = 0;
  virtual void SendData(std::shared_ptr<PipelineData> data) final;
  virtual void RegisterNodeAsNext(std::shared_ptr<Node> nextNode) final;
private:
  void ReceiveData(std::shared_ptr<PipelineData> data);

  std::shared_ptr<Forwarder> forwarder_ {nullptr};
}; // Node

#endif // NODE_HPP_
