#include "stdafx.h"
#include "client.h"

//void L::TCPClient::uploadFile(std::string file_name) {
//	char send_buf[1024] = { 0, };
//	std::ifstream ifs;
//	ifs.open(file_name);
//
//	//std::string fileSize = std::to_string(sizeof(file_name));
//	//m_Socket.write_some(boost::asio::buffer(fileSize));
//
//	while (ifs.getline(send_buf, sizeof(send_buf))) {
//		if (send_buf == NULL) break;
//		std::cout << sizeof(send_buf) << std::endl;
//		m_Socket.write_some(boost::asio::buffer(send_buf));
//		std::cout << " sendData : " << send_buf << std::endl;
//	}
//	
//	strcpy_s(send_buf, "END");
//	m_Socket.write_some(boost::asio::buffer(send_buf));
//
//	ifs.close();
//}

void L::TCPClient::PostWrite() {
	if (m_Socket.is_open() == false)
		return;

	Menu();
	std::cout << "원하는 기능을 입력하세요 : " << std::endl;
	getline(std::cin, option, '\n');
	atoi(option.c_str());

	std::iostream msgBuf_(&postBuf);

	switch ( atoi(option.c_str()) ) {
	case 1:
		msgBuf_ << "getPath";
		msgBuf_ << "\n\n";
		break;

	case 2:
	default :
		std::cout << __FUNCTION__ << "사용법을 확인해 주세요" << std::endl;
	}

	//boost::asio::async_write(m_Socket, boost::asio::buffer(m_WriteMessage),
	async_write(m_Socket, postBuf,
		boost::bind(&TCPClient::writeHandler,
			this,
			placeholders::error,
			placeholders::bytes_transferred)
		);

	PostReceive();
}

void L::TCPClient::PostReceive() {
	//memset(&m_ReceiveBuffer, 0x00, sizeof(m_ReceiveBuffer));
	//std::cout << "Memset Okey" << std::endl;

	m_Socket.async_read_some(getBuf,
		boost::bind(&TCPClient::receiveHandler, 
		    this,
		    placeholders::error,
		    placeholders::bytes_transferred)
	);
}

void L::TCPClient::writeHandler(const boost::system::error_code& error, size_t bytes_transferred) {}

void L::TCPClient::receiveHandler(const boost::system::error_code& error, size_t bytes_transferred) {
	if (error) {
		if (error == error::eof) {
			std::cout << "Server disconnect." << std::endl;
		}
		else {
			std::cout << "error No: " << error.value() << " error Message: " << error.message() << std::endl;
		}
	}
	else {
		std::cout << "====== Message from Server ====== \n"<< std::endl;
		PostWrite();
	}
}


void L::TCPClient::connect(boost::asio::ip::tcp::endpoint& endpoint) {
	m_Socket.async_connect(endpoint,
		boost::bind(&TCPClient::connectHandler,
		    this,
			boost::asio::placeholders::error)
		);
}
void L::TCPClient::connectHandler(const boost::system::error_code& connectErr) {
	if (connectErr) {
		std::cout << "서버 접속 실패 : " << connectErr.message() << std::endl;
	}
	else {
		std::cout << "서버 접속 성공" << std::endl;
		PostWrite();
	}
}


void L::TCPClient::Menu() {
	std::cout << "\n\n================" << std::endl;
	std::cout << "\t파일 시스템 " << std::endl;
	std::cout << "================" << std::endl;
	std::cout << "● 1. 현재 파일 / 폴더 리스트" << std::endl;
	std::cout << "● 2. 폴더 생성" << std::endl;
	std::cout << "● 3. 파일 생성" << std::endl;
	std::cout << "● 4. 폴더 / 파일 삭제" << std::endl;
	std::cout << "● 5. 파일 복사" << std::endl;
	std::cout << "● 6. 폴더 / 파일 이동" << std::endl;
	std::cout << "● 7. 이름 변경" << std::endl;
	std::cout << "● 8. 경로 변경" << std::endl;
	std::cout << "● 9. 파일 다운로드" << std::endl;
	std::cout << "● 10. 파일 업로드" << std::endl;
}