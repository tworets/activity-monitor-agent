#include "http_transport.h"

#include <httplib.h>

#include <string>

constexpr int connectionTimeoutSec{5};
constexpr int readTimeoutSec{5};

bool HttpTransport::send(const std::string& packet) {
  httplib::Client cli(url_);
  if (!cli.is_valid()) {
    return false;
  }

  cli.set_connection_timeout(connectionTimeoutSec);
  cli.set_read_timeout(readTimeoutSec);

  const auto res{cli.Post("/", packet, "application/json")};
  if (!res) {
    return false;
  }

  return res->status >= 200 && res->status < 300;
}