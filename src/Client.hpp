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
	
  void update(World* world, std::string& _player_id);
  void runCommand(const std::string& command, const std::string& id);
  const std::string& getPlayerID() { return player_id; }
private:
  sf::TcpSocket socket;
  std::string player_id;

  sf::Clock update_clock;

};
