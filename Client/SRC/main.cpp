#include "stdafx.h"
#include "client.h"

void main() {
	std::string ip;
	std::string port;

	std::cout << "IP 입력 : ";
	getline(std::cin, ip, '\n');
	std::cout << "Port 입력 : ";
	getline(std::cin, port, '\n');

	io_service ioService;
	tcp::endpoint endpoint(ip::address::from_string(ip), atoi(port.c_str()) );

	L::TCPClient client(ioService, endpoint);

	std::cout << "네트워크 서비스 종료" << std::endl;
	getchar();
}