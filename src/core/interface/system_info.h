#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <string>

class SystemInfo {
 public:
  virtual ~SystemInfo() = default;
  virtual std::string getComputerName() const = 0;
};

#endif
