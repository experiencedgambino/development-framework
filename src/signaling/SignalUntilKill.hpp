#ifndef SIGNALUNTILKILL_HPP_
#define SIGNALUNTILKILL_HPP_

#include <chrono>
#include <signal.h>
#include <thread>

class SignalUntilKill
{
public:
  SignalUntilKill();
  void ReturnOnSignal();

private:
  static void SignalHandler(int signum);

  static const int SLEEP_MILLIS = 1000;

  static bool running_;
}; // SignalUntilKill

#endif // SIGNALUNTILKILL_HPP_
