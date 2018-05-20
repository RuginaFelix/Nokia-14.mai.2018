#include <iostream>

#include "Server.hpp"

int main()
{
	Server MyServer(1111);   

	for (int i = 0; i < NUMBER_OF_CONNECTIONS; ++i)
		MyServer.listenForNewConnection();        

	std::cin.get();
}