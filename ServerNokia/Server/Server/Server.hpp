#ifndef SERVER_FILE_HPP_
#define SERVER_FILE_HPP_

#include "ReceiveMessage.hpp"
#include "SentMessage.hpp"

const int NUMBER_OF_CONNECTIONS = 100;

class Server : public ReceiveMessage, public SentMessage {
public:
	Server(int, bool BroadcastPublically = false);
	bool listenForNewConnection();
private:
	static void clientHandlerThread(int ID);
	bool processPacket(int, Packet);

private:
	int totalConnections_ = 0;
	SOCKET connections_[NUMBER_OF_CONNECTIONS]; 
	SOCKADDR_IN addr_;         
	int addrLen_ = sizeof(addr_);
	SOCKET sListen_;
};

#endif // SERVER_FILE_HPP_