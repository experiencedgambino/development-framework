#ifndef ASYNCNODE_HPP_
#define ASYNCNODE_HPP_

#include "Node.hpp"
#include "AbstractThread.hpp"
#include "MessageQueue.hpp"

class AsyncNode: public Node, public AbstractThread
{
public:
  ~AsyncNode();
  void OnDataAvailable(std::shared_ptr<PipelineData> data) override final;
  void RunThread(void) override final;

  virtual void OnDataAvailableAsync(std::shared_ptr<PipelineData> data) = 0;
private:
  MessageQueue<PipelineData> message_queue_;
  bool thread_finished_ {false};
}; // AsyncNode

#endif // ASYNCNODE_HPP_
