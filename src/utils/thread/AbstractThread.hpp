#ifndef ABSTRACT_THREAD_HPP
#define ABSTRACT_THREAD_HPP

#include <thread>

class AbstractThread
{
public:
  AbstractThread();
  virtual ~AbstractThread();

  virtual bool IsRunning(void) const final;
  virtual void Run(void) final;
  virtual void Stop(void) final;

protected:
  virtual void RunThread(void) = 0;

private:
  bool running_ {false};
  std::thread thread_;
}; // AbstractThread

#endif // ABSTRACT_THREAD_C_HPP
