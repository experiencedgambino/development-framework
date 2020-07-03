#ifndef MESSAGEQUEUE_HPP
#define MESSAGEQUEUE_HPP

#include <deque>
#include <mutex>
#include <semaphore.h>

template<typename T>
class MessageQueue
{
public:
  MessageQueue();
  void Enqueue(std::shared_ptr<T> message);
  std::shared_ptr<T> WaitDequeue(void);

private:
  std::deque<std::shared_ptr<T>> internal_queue_ {};
  sem_t internal_semaphore_;
  std::mutex internal_mutex_;
}; // MessageQueue

template<typename T>
MessageQueue<T>::MessageQueue()
{
  sem_init(&internal_semaphore_, 0, 0);
} // MessageQueue

template<typename T>
void MessageQueue<T>::Enqueue(std::shared_ptr<T> message)
{
  {
    std::lock_guard<std::mutex> current_lock(internal_mutex_);
    internal_queue_.push_back(message);
  }

  sem_post(&internal_semaphore_);
} // Enqueue

template<typename T>
std::shared_ptr<T> MessageQueue<T>::WaitDequeue(void)
{
  sem_wait(&internal_semaphore_);
  std::shared_ptr<T> return_value;

  {
    std::lock_guard<std::mutex> current_lock(internal_mutex_);
    return_value = internal_queue_.front();
    internal_queue_.pop_front();
  }

  return return_value;
} // WaitDequeue

#endif // MESSAGEQUEUE_HPP
