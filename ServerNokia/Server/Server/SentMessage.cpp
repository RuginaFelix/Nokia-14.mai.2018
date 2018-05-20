#include "SentMessage.hpp"

bool SentMessage::sendPacketType(SOCKET& source, Packet _packettype)
{
	int RetnCheck = send(source, (char*)&_packettype, sizeof(Packet), NULL);   
	if (RetnCheck == SOCKET_ERROR)         
		return false;    

	return true;     
}

bool SentMessage::sendInt(SOCKET& source, int _int)
{
	int RetnCheck = send(source, (char*)&_int, sizeof(int), NULL);   
	if (RetnCheck == SOCKET_ERROR)         
		return false;    

	return true;     
}

bool SentMessage::sendString(SOCKET* source, std::string & _string)
{
	if (!sendPacketType(*source, P_ChatMessage))          
		return false;

	int bufferlength = _string.size();    
	if (!sendInt(*source, bufferlength))          
		return false; 

	int RetnCheck = send(*source, _string.c_str(), bufferlength, NULL);   
	if (RetnCheck == SOCKET_ERROR)      
		return false;      

	return true;     
}
