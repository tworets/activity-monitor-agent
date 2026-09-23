#ifndef APPLICATION_H
#define APPLICATION_H

#include "core/agent.h"
#include "core/backup.h"
#include "core/interface/transport.h"
#include "core/metrics.h"
#include "core/packet_builder.h"
#include "core/thread_safe_queue.h"
#include "platform/windows/windows_metrics_collector.h"
#include "platform/windows/windows_system_info.h"
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