#include "core/application.h"
#include "core/interface/stop_signal.h"

int main() {
  installStopHandler();

  Application app;
  app.run();

  signalShutdownComplete();
  return 0;
}