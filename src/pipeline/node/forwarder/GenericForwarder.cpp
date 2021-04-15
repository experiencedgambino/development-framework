#include "GenericForwarder.hpp"

void GenericForwarder::ForwardData(std::shared_ptr<PipelineData> data)
{
  if (receptor_list_.size() != 0)
  {
    index_ = (index_ + 1) % receptor_list_.size();
    receptor_list_[index_]->ReceiveData(data);
  } // if
} // ForwardData

void GenericForwarder::ForwardToNode(std::shared_ptr<Receptor> receptor)
{
  decltype(receptor_list_)::iterator it = std::find(receptor_list_.begin(), receptor_list_.end(), receptor);
  if (it == receptor_list_.end())
  {
    receptor_list_.push_back(receptor);
  } // if
} // ForwardToNode
