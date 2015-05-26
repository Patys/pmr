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


  sf::Packet packet;
  if(socket.receive(packet) == sf::Socket::Status::Done)
    {
      std::string event;
      Enity enity;

      if(packet >> event >> enity)
	{
	  if(event == "new_client")
	    {
	      world->addEnity(enity);
	      std::cout << "New player conected.\n";
	    }
	}
    }
	
}
