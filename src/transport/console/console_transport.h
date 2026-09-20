#ifndef CONSOLE_TRANSPORT_H
#define CONSOLE_TRANSPORT_H

#include "core/transport.h"

class ConsoleTransport : public Transport {
 public:
  bool send(const std::string& packet) override;
};

#endif
