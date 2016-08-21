#include "stdafx.h"
#include "client.h"

void main() {
	std::string ip;
	std::string port;

	std::cout << "IP �Է� : ";
	getline(std::cin, ip, '\n');
	std::cout << "Port �Է� : ";
	getline(std::cin, port, '\n');

	io_service ioService;
	tcp::endpoint endpoint(ip::address::from_string(ip), atoi(port.c_str()) );

	L::TCPClient client(ioService, endpoint);

	std::cout << "��Ʈ��ũ ���� ����" << std::endl;
	getchar();
}