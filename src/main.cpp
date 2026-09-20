#include "core/application.h"

#include "core/stop_signal.h"

#include <iostream>

int main() {
  installStopHandler();

  Application app;
  app.run();

  signalShutdownComplete();
  return 0;
}