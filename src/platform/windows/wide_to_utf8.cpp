#include "platform/windows/wide_to_utf8.h"

#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

#include <string>

std::string wideToUtf8(const std::wstring& ws) {
  if (ws.empty()) {
    return {};
  }

  int neededSize{WideCharToMultiByte(CP_UTF8, 0, ws.data(),
                                     static_cast<int>(ws.size()), nullptr, 0,
                                     nullptr, nullptr)};

  std::string utf8(neededSize, '\0');
  WideCharToMultiByte(CP_UTF8, 0, ws.data(), static_cast<int>(ws.size()),
                      utf8.data(), neededSize, nullptr, nullptr);

  return utf8;
}
