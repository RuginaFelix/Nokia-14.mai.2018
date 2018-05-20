#include "Client.hpp"

static Client* clientPtr;

Client::Client(std::string IP, int PORT)
{
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);

	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(0);
	}

	addr_.sin_addr.s_addr = inet_addr(IP.c_str());      
	addr_.sin_port = htons(PORT);    
	addr_.sin_family = AF_INET;  
	clientPtr = this;             
}

bool Client::Connect()
{
	connection_ = socket(AF_INET, SOCK_STREAM, NULL);   
	if (connect(connection_, (SOCKADDR*)&addr_, sizeOfAddr_) != 0)
	{
		MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	std::cout << "Connected!" << std::endl;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)clientThread, NULL, NULL, NULL);             
	return true;
}

SOCKET* Client::getSocket()
{
	return &connection_;
}

void Client::clientThread()
{
	Packet PacketType;
	while (true)
	{
		if (!clientPtr->GetPacketType(&(clientPtr->connection_), PacketType))   
			break;            
		if (!clientPtr->processPacket(clientPtr->connection_, PacketType))    
			break;           
	}
	std::cout << "Lost connection to the server." << std::endl;
	if (clientPtr->closeConnection())           
		std::cout << "Socket to the server was closed successfuly." << std::endl;
	else             
		std::cout << "Socket was not able to be closed." << std::endl;
}

bool Client::closeConnection()
{
	if (closesocket(connection_) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAENOTSOCK)                     
			return true;        

		std::string ErrorMessage = "Failed to close the socket. Winsock Error: " + std::to_string(WSAGetLastError()) + ".";
		MessageBoxA(NULL, ErrorMessage.c_str(), "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

bool Client::processPacket(SOCKET& source, Packet _packettype)
{
	switch (_packettype)
	{
	case P_ChatMessage:       
	{
		std::string Message;       
		if (!GetString(source, Message))          
			return false;           
		std::cout << Message << std::endl;      
		break;
	}
	default:       
		std::cout << "Unrecognized packet: " << _packettype << std::endl;      
		break;
	}
	return true;
}
