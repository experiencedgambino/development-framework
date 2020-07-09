#include "SignalUntilKill.hpp"

bool SignalUntilKill::running_ {false};
const int SignalUntilKill::SLEEP_MILLIS;

SignalUntilKill::SignalUntilKill()
{
  signal(SIGKILL, SignalUntilKill::SignalHandler);
  signal(SIGQUIT, SignalUntilKill::SignalHandler);
  signal(SIGTERM, SignalUntilKill::SignalHandler);
  signal(SIGINT, SignalUntilKill::SignalHandler);
} // SignalUntilKill

void SignalUntilKill::SignalHandler(int signum)
{
  running_ = false;
} // SignalHandler

void SignalUntilKill::ReturnOnSignal()
{
  running_ = true;
  while (running_ == true)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLIS));
  } // while
} // ReturnOnSignal
