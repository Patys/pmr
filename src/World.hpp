#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <string>
#include <vector>
#include "Enity.hpp"
#include "Player.hpp"

class World
{
public:
  
  void changeWorld(World* world);

  void addEnity(Enity enity);
  Enity* getEnity(const std::string& id);
  void removeEnity(const std::string& id);

  void addPlayer(Player player);
  Player* getPlayer(const std::string& id);
  void removePlayer(const std::string& id);

  std::vector<Enity> enities;
  std::vector<Player> players;
};

sf::Packet& operator <<(sf::Packet& packet, const World& m);
sf::Packet& operator >>(sf::Packet& packet, World& m);
