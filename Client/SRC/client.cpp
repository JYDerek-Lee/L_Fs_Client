#include "stdafx.h"
#include "client.h"

void L::TCP_Client::upload(std::string file_name) {
	char send_buf[1024] = { 0, };
	std::string res;
	std::ifstream ifs;
	ifs.open(file_name);

	while (ifs.getline(send_buf, sizeof(send_buf))) {
		//res += send_buf;
		m_Socket.write_some(boost::asio::buffer(res));
		//res += '\n';
	}
	//m_Socket.write_some(boost::asio::buffer(res));
	ifs.close();
}
void L::TCP_Client::PostWrite() {
	std::string m_WriteMessage;
	std::string mbuffer;
	Menu();

	if (m_Socket.is_open() == false) {
		return;
	}
	getline(std::cin, m_WriteMessage);

	std::stringstream msgBuffer(m_WriteMessage);
	msgBuffer >> mbuffer;

	if (mbuffer == "upload") {
		boost::asio::async_write(m_Socket, boost::asio::buffer(m_WriteMessage),
			boost::bind(&TCP_Client::handle_write, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred)
			);
		msgBuffer >> mbuffer;
		upload(mbuffer);
	}
	else {
		boost::asio::async_write(m_Socket, boost::asio::buffer(m_WriteMessage),
			boost::bind(&TCP_Client::handle_write, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred)
			);
	}
	PostReceive();
}

void L::TCP_Client::PostReceive() {
	memset(&m_ReceiveBuffer, 0x00, sizeof(m_ReceiveBuffer));

	m_Socket.async_read_some(boost::asio::buffer(m_ReceiveBuffer),
		boost::bind(&TCP_Client::handle_receive, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred)
		);

}

void L::TCP_Client::handle_connect(const boost::system::error_code& error) {
	if (error) {
		std::cout << "connect failed : " << error.message() << std::endl;
	}
	else {
		std::cout << "connected" << std::endl;

		PostWrite();
	}
}

void L::TCP_Client::handle_write(const boost::system::error_code& error, size_t bytes_transferred) {}
void L::TCP_Client::handle_receive(const boost::system::error_code& error, size_t bytes_transferred) {
	if (error) {
		if (error == boost::asio::error::eof) {
			std::cout << "Server disconnect." << std::endl;
		}
		else {
			std::cout << "error No: " << error.value() << " error Message: " << error.message() << std::endl;
		}
	}
	else {
		const std::string strRecvMessage = m_ReceiveBuffer;
		std::cout << "Message from Server: " << strRecvMessage << std::endl;
		PostWrite();
	}
}

void L::TCP_Client::Menu() {
	std::cout << "========== Menual ==========" << std::endl;
	std::cout << "1. Path (pwd)" << std::endl;
	std::cout << "2. File / Forder List (ls)" << std::endl;
	std::cout << "3. Create Forder (mkdir ForderName)" << std::endl;
	std::cout << "4. Remove Forder (rm ForderName || rmdir ForderName)" << std::endl;
	std::cout << "5. Create File (mkfile FileName)" << std::endl;
	std::cout << "6. Remove File (rm FileName)" << std::endl;
	std::cout << "7. Rename (rename cur dest)" << std::endl;
	std::cout << "8. Upload File (upload FileName)" << std::endl;
}