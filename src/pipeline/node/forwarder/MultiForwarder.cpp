#include "MultiForwarder.hpp"

void MultiForwarder::ForwardData(std::shared_ptr<PipelineData> data)
{
  // Temp pointer to data to copy
  std::shared_ptr<PipelineData> copy = nullptr;
  for (auto & receptor : receptor_list_)
  {
    copy = std::make_shared<PipelineData>();
    *copy = *data;
    receptor->ReceiveData(copy);
  } // for

} // ForwardData

void MultiForwarder::ForwardToNode(std::shared_ptr<Receptor> receptor)
{
  decltype(receptor_list_)::iterator it = std::find(receptor_list_.begin(), receptor_list_.end(), receptor);
  if (it == receptor_list_.end())
  {
    receptor_list_.push_back(receptor);
  } // if
} // ForwardToNode
