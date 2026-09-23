#include "transport/http/http_transport.h"

#include <httplib.h>

#include <string>

namespace {

constexpr int connectionTimeoutSec{5};
constexpr int readTimeoutSec{5};

}  // namespace

bool HttpTransport::send(const std::string& packet) const {
  httplib::Client cli(url_);
  if (!cli.is_valid()) {
    return false;
  }

  cli.set_connection_timeout(connectionTimeoutSec);
  cli.set_read_timeout(readTimeoutSec);

  const auto result{cli.Post("/", packet, "application/json")};
  if (!result) {
    return false;
  }

  return result->status >= 200 && result->status < 300;
}