#pragma once

#include "World.hpp"

class Client
{
public:
  Client();

  void connect(const std::string& ip);

  inline const std::string& getPlayerID() { return player_id; }

  // process server's data
  void update(World* world);

  // send command to server
  void sendCommand(const std::string& command, std::vector<std::string> additional_data);
private:
  sf::TcpSocket socket;

  std::string player_id;
};
