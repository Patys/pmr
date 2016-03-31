#pragma once

#include "World.hpp"

class Server
{
public:
	Server();

	void setup();

	void update();

private:

	void excuteCommand(const std::string& command, std::vector<std::string> data, sf::TcpSocket* client);

	sf::TcpListener listener;
	std::vector < sf::TcpSocket *> clients;
	sf::SocketSelector selector;

	World world;
};
