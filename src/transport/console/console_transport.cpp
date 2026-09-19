#include "console_transport.h"

#include <iostream>

bool ConsoleTransport::send(const std::string& packet) {

	std::cout << packet << std::endl;

	return true;

}