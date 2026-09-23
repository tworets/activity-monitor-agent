#ifndef BACKUP_H
#define BACKUP_H

#include "core/metrics.h"

#include <deque>
#include <optional>
#include <string>
#include <utility>

class Backup {
 public:
  explicit Backup(std::string path = "backup.json") : path_(std::move(path)) {}

  bool saveBackup(const std::deque<Metrics>& metrics);
  std::optional<std::deque<Metrics>> loadBackup();
  bool removeBackup();

 private:
  std::string path_{};
};

#endif