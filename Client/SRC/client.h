#include "stdafx.h"

const char SERVER_IP[] = "127.0.0.1";
const unsigned short PORT_NUMBER = 31400;

namespace L {
	class TCP_Client {
	public:
		TCP_Client(boost::asio::io_service& io_service)
			: m_io_service(io_service),
			m_Socket(io_service) {}

		void Connect(boost::asio::ip::tcp::endpoint& endpoint) {
			m_Socket.async_connect(endpoint,
				boost::bind(&TCP_Client::handle_connect,
				this,
				boost::asio::placeholders::error)
				);
		}

	private:
		void Menu();
		void PostWrite();
		void PostReceive();
		void upload(std::string file_name);
		void handle_connect(const boost::system::error_code& error);
		void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
		void handle_receive(const boost::system::error_code& error, size_t bytes_transferred);

		boost::asio::io_service& m_io_service;
		boost::asio::ip::tcp::socket m_Socket;
		char m_ReceiveBuffer[10000];
	};
}