#ifndef RECEIVEMESSAGE_FILE_HPP_
#define RECEIVEMESSAGE_FILE_HPP_

#pragma comment(lib,"ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#include <string>

#include "Packet.hpp"

class ReceiveMessage {
protected:
	bool getInt(SOCKET&, int&);
	bool getString(SOCKET&, std::string&);
	bool getPacketType(SOCKET*, Packet&);
};

#endif // RECEIVEMESSAGE_FILE_HPP_