#ifndef METRICS_JSON_H
#define METRICS_JSON_H

#include "core/metrics.h"

#include <nlohmann/json.hpp>

inline void to_json(nlohmann::json& j, const Metrics& m) {
  j = nlohmann::json{{"time", m.time},
                     {"process_name", m.processName},
                     {"window_title", m.windowTitle},
                     {"user_active", m.userActive}};
}

inline void from_json(const nlohmann::json& j, Metrics& m) {
  j.at("time").get_to(m.time);
  j.at("process_name").get_to(m.processName);
  j.at("window_title").get_to(m.windowTitle);
  j.at("user_active").get_to(m.userActive);
}

#endif