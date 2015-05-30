#include "Item.hpp"

sf::Packet& operator <<(sf::Packet& packet, const Item& m)
{
  return packet << m.position.x << m.position.y << m.size.x << m.size.y <<  m.id << m.type;
}

sf::Packet& operator >>(sf::Packet& packet, Item& m)
{
  return packet >> m.position.x >> m.position.y >> m.size.x >> m.size.y >>  m.id >> m.type;
}

sf::Packet& operator <<(sf::Packet& packet, const std::vector<Item>& m)
{
  packet << m.size();
  for(std::size_t i = 0; i < m.size(); i++)
    {
      packet << m[i];
    }
  return packet;
}

sf::Packet& operator >>(sf::Packet& packet, std::vector<Item>& m)
{
  std::size_t size;
  packet >> size;
  m.reserve(size);
  for(std::size_t i = 0; i < size; i++)
    {
      Item temp;
      packet >> temp;
      m.push_back(temp);
    }
  return packet;
}
