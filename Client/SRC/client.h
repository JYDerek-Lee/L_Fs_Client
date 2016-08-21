#include "stdafx.h"
//const char SERVER_IP[] = "127.0.0.1";
//const unsigned short PORT_NUMBER = 6666;

namespace L {
	class TCPClient {
	private:
		streambuf getBuf;
		streambuf postBuf;
		std::string option;
		tcp::socket m_Socket;
		io_service& m_ioService;
		tcp::endpoint m_Endpoint;

		//std::string mbuffer;
		//char m_ReceiveBuffer[1024];
		//std::string m_WriteMessage;

		void Menu();
		void PostWrite();
		void PostReceive();
		//void uploadFile(std::string file_name);
		void connect(tcp::endpoint& endpoint);
		void connectHandler(const boost::system::error_code& connectErr);
		void writeHandler(const boost::system::error_code& writeErr, size_t bytes_transferred);
		void receiveHandler(const boost::system::error_code& receiveErr, size_t bytes_transferred);


	public:
		TCPClient(io_service& ioService, tcp::endpoint endpoint) 
			: m_ioService(ioService), m_Socket(ioService), m_Endpoint(endpoint) {
			connect(m_Endpoint);
			m_ioService.run();
		}
	};
}