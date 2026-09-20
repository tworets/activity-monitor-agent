#include "application.h"

#include "interface/stop_signal.h"

#include <filesystem>
#include <iostream>
#include <utility>

namespace {

constexpr std::size_t maxQueueSize{100};
constexpr const char* serverUrl{"127.0.0.1:8080"};
constexpr const char* backupPath{"backup.json"};

}  // namespace

Application::Application()
    : systemInfo_(),
      collector_(),
      queue_(maxQueueSize),
      transport_(serverUrl),
      backup_(backupPath),
      packetBuilder_(systemInfo_.getComputerName()),
      agent_(collector_, queue_, transport_, packetBuilder_) {}

void Application::run() {
  auto restored{backup_.loadBackup()};
  if (restored && !restored->empty()) {
    for (auto& m : *restored) {
      queue_.push(std::move(m));
    }
    backup_.removeBackup();
  }

  agent_.start();

  waitForStopSignal();

  agent_.stop();

  auto remaining{queue_.extractAll()};
  if (!remaining.empty()) {
    backup_.saveBackup(remaining);
  }
}