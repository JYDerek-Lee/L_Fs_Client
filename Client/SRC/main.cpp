#include "stdafx.h"
#include "client.h"

int main() {
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(SERVER_IP), PORT_NUMBER);

	L::TCP_Client client(io_service);

	client.Connect(endpoint);

	io_service.run();

	std::cout << "Network Service exit..." << std::endl;

	getchar();
	return 0;
}