#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <string>

class Transport {
 public:
  virtual ~Transport() = default;
  virtual bool send(const std::string& packet) = 0;
};

#endif