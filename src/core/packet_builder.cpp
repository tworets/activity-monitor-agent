#include "core/packet_builder.h"

#include "core/metrics.h"
#include "core/metrics_json.h"

#include <nlohmann/json.hpp>

#include <chrono>
#include <deque>

std::string PacketBuilder::build(const std::deque<Metrics>& metrics) const {
  const auto now{std::chrono::system_clock::now()};
  const auto timestamp{
      std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch())
          .count()};

  nlohmann::json packet;
  packet["agent_id"] = agentId_;
  packet["timestamp"] = timestamp;
  packet["payload"] = metrics;

  return packet.dump();
}