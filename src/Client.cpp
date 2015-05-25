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
  std::string s = "Hello!";
  packet << s;
  if(socket.send(packet) != sf::Socket::Done)
    {
      std::cout << "Data not send!\n";
    }
	
}
