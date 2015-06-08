#include "Client.hpp"
#include <iostream>

#define PLAYER_SPEED 4

Client::Client()
{
	
}

Client::~Client()
{
	
}

void Client::init(const std::string& ip)
{
  socket.setBlocking(false);
  socket.connect(ip, 28282);
}

void Client::update(World* world, std::string& _player_id)
{
  // Here update
  // Reciving and sending data to server
  sf::Packet packet;
  if(socket.receive(packet) == sf::Socket::Status::Done)
    {
      std::string event;

      if(packet >> event)
	{
	  if(event == "update world")
	    {
	      World new_world;
	      
	      if(packet >> new_world)
		{
		  world->changeWorld(&new_world);
		}
	    }

	  if(event == "connect")
	    {
	      Player new_player;

	      if(packet >> new_player)
		{
		  player_id = new_player.id;
		  _player_id = player_id;
		  world->addPlayer(new_player);
		  std::cout << player_id << " Connected.\n";
		}
	    }
	}
    }

  sf::Packet update_packet;
  update_packet << "update world";
  socket.send(update_packet);
}

void Client::runCommand(const std::string& command, const std::string& id)
{
  if(command == "player move")
    {
      sf::Packet packet;
      packet << "player move" << id << player_id;
      socket.send(packet);
    }
  if(command == "destroy item")
    {
      sf::Packet packet;
      packet << "destroy item" << id;
      socket.send(packet);
    }
  if(command == "pick up")
    {
      sf::Packet packet;
      packet << "pick up" << id << player_id;
      socket.send(packet);
    }
  if(command == "drop item")
    {
      sf::Packet packet;
      packet << "drop item" << id << player_id;
      socket.send(packet);
    }
  if(command == "attack enity")
    {
      sf::Packet packet;
      packet << "attack enity" << id;
      socket.send(packet);
    }
}
