#include "World.hpp"

void World::addEnity(Enity enity)
{
  enities.push_back(enity);
}

Enity* World::getEnity(const std::string& id)
{
  for(std::size_t i = 0; i < enities.size(); i++)
    {
      if(enities[i].id == id)
  	{
  	  return &enities[i];
  	}
    }
  return nullptr;
}

void World::removeEnity(const std::string& id)
{
  for(std::size_t i = 0; i < enities.size(); i++)
    {
      if(enities[i].id == id)
	{
	  enities.erase(enities.begin() + i);
	  return;
	}
    }
}

void World::addItem(Item item)
{
  items.push_back(item);
}

Item* World::getItem(const std::string& id)
{
  for(std::size_t i = 0; i < items.size(); i++)
    {
      if(items[i].id == id)
  	{
  	  return &items[i];
  	}
    }
  return nullptr;
}

void World::removeItem(const std::string& id)
{
  for(std::size_t i = 0; i < items.size(); i++)
    {
      if(items[i].id == id)
	{
	  items.erase(items.begin() + i);
	  return;
	}
    }
}

void World::addPlayer(Player player)
{
  players.push_back(player);
}

Player* World::getPlayer(const std::string& id)
{
  for(std::size_t i = 0; i < players.size(); i++)
    {
      if(players[i].id == id)
  	{
  	  return &players[i];
  	}
    }
  return nullptr;
}

void World::removePlayer(const std::string& id)
{
  for(std::size_t i = 0; i < players.size(); i++)
    {
      if(players[i].id == id)
	{
	  players.erase(players.begin() + i);
	  return;
	}
    }
}

sf::Packet& operator <<(sf::Packet& packet, const World& m)
{
  return packet << m.enities << m.items << m.players;
}

sf::Packet& operator >>(sf::Packet& packet, World& m)
{
  return packet >> m.enities >> m.items >> m.players;
}
