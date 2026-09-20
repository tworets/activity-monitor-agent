#ifndef HTTP_TRANSPORT_H
#define HTTP_TRANSPORT_H

#include "core/interface/transport.h"

#include <string>

class HttpTransport : public Transport {
 public:
  explicit HttpTransport(const std::string& url) : url_(url) {};
  bool send(const std::string& packet) override;

 private:
  std::string url_;
};

#endif