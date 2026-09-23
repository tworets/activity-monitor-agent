#ifndef METRICS_COLLECTOR_H
#define METRICS_COLLECTOR_H

#include "core/metrics.h"

class MetricsCollector {
 public:
  virtual ~MetricsCollector() = default;
  virtual Metrics collect() const = 0;
};

#endif