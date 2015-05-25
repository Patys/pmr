#pragma once

#include <string>
#include <vector>
#include <SFML/Network.hpp>
#include "World.hpp"

class Server
{
public:
  Server();
  ~Server();
	
  void init();
	
  void update(World* world);
private:
  sf::TcpListener listener;
  std::vector < sf::TcpSocket *> clients;
  sf::SocketSelector selector;
};
