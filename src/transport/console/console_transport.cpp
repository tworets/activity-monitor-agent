#include "transport/console/console_transport.h"

#include <iostream>

bool ConsoleTransport::send(const std::string& packet) const {
  std::cout << packet << '\n';

  return true;
}