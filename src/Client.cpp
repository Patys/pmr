#include "Client.hpp"
#include <iostream>

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

void Client::update(World* world)
{
  // Here update
  // Reciving and sending data to server

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
      world->getEnity(player_id)->position.y -= 1;
    }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
      world->getEnity(player_id)->position.y += 1;
    }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
      world->getEnity(player_id)->position.x -= 1;
    }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
      world->getEnity(player_id)->position.x += 1;
    }

  sf::Packet packet;
  if(socket.receive(packet) == sf::Socket::Status::Done)
    {
      std::string event;
      Enity enity;

      if(packet >> event)
	{
	  if(event == "world_update")
	    {
	      std::vector<Enity> updated_world;
	      
	      if(packet >> updated_world)
		{
		  world->changeWorld(updated_world);
		}
	    }

	  if(event == "connected")
	    {
	      if(packet >> enity)
		{
		  player_id = enity.id;
		  world->addEnity(enity);
		  std::cout << player_id << " Connected.\n";
		}
	    }
	}
    }
  
  if(update_clock.getElapsedTime().asMilliseconds() > 100)
    {
      sf::Packet update_packet;
      update_packet << "update_position" << *world->getEnity(player_id);
      socket.send(update_packet);
      update_clock.restart();
    }

}
