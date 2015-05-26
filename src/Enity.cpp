#include "Enity.hpp"


sf::Packet& operator <<(sf::Packet& packet, const Enity& m)
{
  return packet << m.position.x << m.position.y << m.size.x << m.size.y << m.life << m.type << m.id;
}

sf::Packet& operator >>(sf::Packet& packet, Enity& m)
{
  return packet >> m.position.x >> m.position.y >> m.size.x >> m.size.y >> m.life >> m.type >> m.id;
}
