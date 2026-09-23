#ifndef WINDOWS_METRICS_COLLECTOR_H
#define WINDOWS_METRICS_COLLECTOR_H

#include "core/interface/metrics_collector.h"
#include "core/metrics.h"

class WindowsMetricsCollector : public MetricsCollector {
 public:
  Metrics collect() const override;
};

#endif
