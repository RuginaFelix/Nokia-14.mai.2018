#include "ReceiveMessage.hpp"

bool ReceiveMessage::GetString(SOCKET& source, std::string & _string)
{
	int bufferLength;     

	if (!getInt(source, bufferLength))          
		return false;      

	char* buffer = new char[bufferLength + 1];  
	buffer[bufferLength] = '\0';     
	int RetnCheck = recv(source, buffer, bufferLength, NULL);                           
	
	_string = buffer; 
	delete[] buffer;        

	if (RetnCheck == SOCKET_ERROR)       
		return false;      

	return true;         
}

bool ReceiveMessage::GetPacketType(SOCKET* source, Packet & _packettype)
{
	int RetnCheck = recv(*source, (char*)&_packettype, sizeof(Packet), NULL); 
	if (RetnCheck == SOCKET_ERROR)      
		return false;           

	return true;          
}

bool ReceiveMessage::getInt(SOCKET& source, int & _int)
{
	int RetnCheck = recv(source, (char*)&_int, sizeof(int), NULL);  
	if (RetnCheck == SOCKET_ERROR)      
		return false;

	return true;         
}
