#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <string>
#include <vector>
#include "Enity.hpp"
#include "Player.hpp"
#include "Item.hpp"

class World
{
public:
  
  void changeWorld(World* world) 
  { 
    enities.clear(); enities.swap(world->enities);
    items.clear(); items.swap(world->items);
    players.clear(); players.swap(world->players);
  }

  void addEnity(Enity enity);
  Enity* getEnity(const std::string& id);
  void removeEnity(const std::string& id);

  void addItem(Item item);
  Item* getItem(const std::string& id);
  void removeItem(const std::string& id);

  void addPlayer(Player player);
  Player* getPlayer(const std::string& id);
  void removePlayer(const std::string& id);

  std::vector<Enity> enities;
  std::vector<Item> items;
  std::vector<Player> players;
};

sf::Packet& operator <<(sf::Packet& packet, const World& m);
sf::Packet& operator >>(sf::Packet& packet, World& m);
