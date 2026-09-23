#ifndef HTTP_TRANSPORT_H
#define HTTP_TRANSPORT_H

#include "core/interface/transport.h"

#include <string>
#include <utility>

class HttpTransport : public Transport {
 public:
  explicit HttpTransport(std::string url) : url_(std::move(url)) {}
  bool send(const std::string& packet) const override;

 private:
  std::string url_{};
};

#endif