#ifndef WINDOWS_METRICS_COLLECTOR_H
#define WINDOWS_METRICS_COLLECTOR_H

#include "core/metrics.h"
#include "core/metrics_collector.h"

class WindowsMetricsCollector : public MetricsCollector {
 public:
  Metrics collect() override;
};

#endif
