#ifndef CLIENT_FILE_HPP_
#define CLIENT_FILE_HPP_

#include "ReceiveMessage.hpp"
#include "SentMessage.hpp"

class Client : public ReceiveMessage, public SentMessage {
public:
	Client(std::string, int);
	bool Connect();
	bool closeConnection();
	SOCKET* getSocket();
private:
	bool processPacket(SOCKET&, Packet);
	static void clientThread();

private:
	SOCKET connection_;     
	SOCKADDR_IN addr_;        
	int sizeOfAddr_ = sizeof(addr_);      
};

#endif // CLIENT_FILE_HPP_