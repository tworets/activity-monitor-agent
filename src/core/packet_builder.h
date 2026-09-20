#ifndef PACKET_BUILDER_H
#define PACKET_BUILDER_H

#include "metrics.h"

#include <deque>
#include <string>
#include <utility>

class PacketBuilder {
 public:
  explicit PacketBuilder(std::string agentId) : agentId_{std::move(agentId)} {};

  std::string build(const std::deque<Metrics>& metrics) const;

 private:
  std::string agentId_;
};

#endif