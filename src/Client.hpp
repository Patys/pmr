#pragma once

#include <string>
#include <SFML/Network.hpp>
#include "World.hpp"

class Client
{
public:
  Client();
  ~Client();
	
  void init(const std::string& ip);
	
  void update(World* world);
private:
  sf::TcpSocket socket;
  std::string player_id;

  sf::Clock update_clock;

};
