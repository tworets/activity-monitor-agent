#ifndef METRICS_COLLECTOR_H
#define METRICS_COLLECTOR_H

#include "metrics.h"

class MetricsCollector {

	public: 

		virtual ~MetricsCollector() = default;
		virtual Metrics collect() = 0;

};

#endif