#include "AbstractThread.hpp"

AbstractThread::AbstractThread()
{

} // AbstractThread
AbstractThread::~AbstractThread()
{

}// ~AbstractThread

bool AbstractThread::IsRunning(void) const
{
  return running_;
}

void AbstractThread::Run(void)
{
  running_ = true;
  thread_ = std::thread(&AbstractThread::RunThread, this);
} // Run

void AbstractThread::Stop(void)
{
  thread_.join();
} // Stop
