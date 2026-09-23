#ifndef WINDOWS_SYSTEM_INFO_H
#define WINDOWS_SYSTEM_INFO_H

#include "core/interface/system_info.h"

#include <string>

class WindowsSystemInfo : public SystemInfo {
 public:
  std::string getComputerName() const override;
};

#endif