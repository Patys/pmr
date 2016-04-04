#pragma once

#include "World.hpp"

class Client
{
public:
	static void connect(const std::string& ip);

	static inline const std::string& getPlayerID() { return player_id; }

	// process server's data
	static void update(World* world);

	// send command to server
	static void sendCommand(const std::string& command, std::vector<std::string> additional_data);
private:
	static sf::TcpSocket socket;

	static std::string player_id;
};
