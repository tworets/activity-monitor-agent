#include "core/stop_signal.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

namespace {

HANDLE g_stopEvent{nullptr};
HANDLE g_shutdownCompleteEvent{nullptr};

constexpr DWORD shutdownWaitMs{4000};

BOOL WINAPI consoleHandler(DWORD signal) {
  const bool isStopEvent{signal == CTRL_C_EVENT || signal == CTRL_BREAK_EVENT ||
                         signal == CTRL_CLOSE_EVENT ||
                         signal == CTRL_LOGOFF_EVENT ||
                         signal == CTRL_SHUTDOWN_EVENT};

  if (!isStopEvent) {
    return FALSE;
  }

  if (g_stopEvent) {
    SetEvent(g_stopEvent);
  }

  const bool isForcedShutdown{signal == CTRL_CLOSE_EVENT ||
                              signal == CTRL_LOGOFF_EVENT ||
                              signal == CTRL_SHUTDOWN_EVENT};

  if (isForcedShutdown && g_shutdownCompleteEvent) {
    WaitForSingleObject(g_shutdownCompleteEvent, shutdownWaitMs);
  }

  return TRUE;
}

}  // namespace

void installStopHandler() {
  g_stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
  g_shutdownCompleteEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
  SetConsoleCtrlHandler(consoleHandler, TRUE);
}

void waitForStopSignal() {
  if (g_stopEvent) {
    WaitForSingleObject(g_stopEvent, INFINITE);
  }
}

void signalShutdownComplete() {
  if (g_shutdownCompleteEvent) {
    SetEvent(g_shutdownCompleteEvent);
  }
}