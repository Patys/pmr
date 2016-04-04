#include "Client.hpp"
#include <iostream>

sf::TcpSocket Client::socket;
std::string Client::player_id;


void Client::connect(const std::string& ip)
{
	socket.setBlocking(false);
	socket.connect(ip, 28282);
}

void Client::update(World* world)
{
	// get data from server
	sf::Packet packet;

	if(Client::socket.receive(packet) == sf::Socket::Status::Done)
	{
		std::string event;

		if(packet >> event)
		{
			if(event == "connect")
			{
				std::string new_player_id;
				if(packet >> new_player_id)
				{
					Client::player_id = new_player_id;
					std::cout << "Player ID: " << player_id << "\n";
				}
			}

			if(event == "update world")
			{
				World new_world;
				if(packet >> new_world)
				{
					world->changeWorld(&new_world);
				}
			}
		}
	}

	// send we want new updated world
	sendCommand("update world", {""});
}

void Client::sendCommand(const std::string& command, std::vector<std::string> additional_data)
{
	sf::Packet packet;

	// we wrap command, number of data and all data

	packet << command << additional_data.size();

	for(auto x : additional_data)
	{
		packet << x;
	}

	socket.send(packet);
}
