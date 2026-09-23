#include "core/agent.h"

#include <chrono>
#include <mutex>
#include <utility>

void Agent::collectorLoop() {
  while (!stopRequested_) {
    queue_.push(collector_.collect());

    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait_for(lock, std::chrono::seconds(5),
                 [this] { return stopRequested_.load(); });
  }
}

void Agent::transportLoop() {
  auto lastFlush{std::chrono::steady_clock::now()};

  while (!stopRequested_) {
    const auto batch{queue_.peekAll()};
    const auto now{std::chrono::steady_clock::now()};
    const auto elapsed{
        std::chrono::duration_cast<std::chrono::seconds>(now - lastFlush)
            .count()};

    const bool timeToFlush{elapsed >= 30};
    const bool enoughToFlush{batch.size() >= 10};

    if (batch.empty() || (!timeToFlush && !enoughToFlush)) {
      std::unique_lock<std::mutex> lock(mutex_);
      cv_.wait_for(lock, std::chrono::milliseconds(100),
                   [this] { return stopRequested_.load(); });
      continue;
    }

    const std::string packet{packetBuilder_.build(batch)};
    if (transport_.send(packet)) {
      queue_.removeFront(batch.size());
      lastFlush = now;
      continue;
    }

    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait_for(lock, std::chrono::seconds(10),
                 [this] { return stopRequested_.load(); });
  }
}

void Agent::start() {
  collectorThread_ = std::thread([this] { collectorLoop(); });
  transportThread_ = std::thread([this] { transportLoop(); });
}

void Agent::stop() {
  stopRequested_ = true;
  cv_.notify_all();
  queue_.stop();

  if (collectorThread_.joinable()) {
    collectorThread_.join();
  }
  if (transportThread_.joinable()) {
    transportThread_.join();
  }
}