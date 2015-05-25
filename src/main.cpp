#include "Game.hpp"
#include <iostream>
#include <string>

int main()
{
	int answ = 0;
	std::cout << "#Menu\n 1 - Client\n 2 - Server" << std::endl;
	std::cin >> answ;
	
	
	if(answ == 1)
	{
		std::string ip;
		std::cout << "Type server IP: " << std::endl;
		std::cin >> ip;
		Game game;
		game.runClient(ip);
	}
	if(answ == 2)
	{
		std::cout << "Server IP is computer IP." << std::endl;
		Game game;
		game.runServer();
	}
	return 0;
}
