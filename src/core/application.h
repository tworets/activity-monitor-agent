#ifndef APPLICATION_H
#define APPLICATION_H

#include "agent.h"
#include "backup.h"
#include "metrics.h"
#include "packet_builder.h"
#include "platform/windows/windows_metrics_collector.h"
#include "platform/windows/windows_system_info.h"
#include "thread_safe_queue.h"
#include "transport.h"
#include "transport/http/http_transport.h"

class Application {
 public:
  Application();

  void run();

 private:
  WindowsSystemInfo systemInfo_;
  WindowsMetricsCollector collector_;
  ThreadSafeQueue<Metrics> queue_;
  HttpTransport transport_;
  Backup backup_;
  PacketBuilder packetBuilder_;
  Agent agent_;
};

#endif