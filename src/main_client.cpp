#include "client/Client.hpp"
#include <iostream>
#include "stdxx/log.hxx"

int main() {
	client::Client client;
	stx::log.register_output(std::cout);
	client.run();
	return 0;
}
