#include "AbstractThread.hpp"

#include <iostream>

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
  running_ = false;
  thread_.join();
} // Stop

void AbstractThread::DetachStop(void)
{
  thread_.detach();
  running_ = false;
} // Stop
