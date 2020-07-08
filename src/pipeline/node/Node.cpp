#include "Node.hpp"
#include <iostream>
Node::Node(std::shared_ptr<Forwarder> forwarder):
  forwarder_(forwarder)
{

} // Node

void Node::SendData(std::shared_ptr<PipelineData> data)
{
  forwarder_->ForwardData(data);
} // SendData

void Node::RegisterNodeAsNext(std::shared_ptr<Node> nextNode)
{
  forwarder_->ForwardToNode(nextNode);
} // RegisterNodeAsNext

void Node::ReceiveData(std::shared_ptr<PipelineData> data)
{
  OnDataAvailable(data);
} // ReceiveData
