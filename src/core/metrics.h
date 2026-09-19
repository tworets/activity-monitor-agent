#ifndef METRICS_H
#define METRICS_H

#include <string>

struct Metrics {

	std::string time{};
	std::string processName{};
	std::string windowTitle{};
	bool userActive{};

};

#endif