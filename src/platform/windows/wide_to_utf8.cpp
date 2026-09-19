#include "wide_to_utf8.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include <string>

std::string wideToUtf8(const std::wstring& wstring) {

    if (wstring.empty()) return {};

    int neededSize { WideCharToMultiByte(CP_UTF8, 0, wstring.data(),
        static_cast<int>(wstring.size()),
        nullptr, 0, nullptr, nullptr) };

    std::string utf8(neededSize, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wstring.data(), static_cast<int>(wstring.size()),
        utf8.data(), neededSize, nullptr, nullptr);

    return utf8;
}
