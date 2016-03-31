#include "Enity.hpp"

const std::string&  getItemDescription(const std::string& type)
{
  std::string sword1 = "Beautiful, ancient sword used by many powerfull warriors.";
  std::string axe1 = "One-handed, sharp axe.";

  if(type == "sword1")
    return sword1;
  if(type == "axe1")
    return axe1;

  return "This item has no description.";
}

sf::Packet& operator <<(sf::Packet& packet, const Enity& m)
{
	return packet << m.position.x << m.position.y << m.size.x << m.size.y << m.attackable << m.life << m.type << m.id;
}

sf::Packet& operator >>(sf::Packet& packet, Enity& m)
{
	return packet >> m.position.x >> m.position.y >> m.size.x >> m.size.y >> m.attackable >> m.life >> m.type >> m.id;
}

sf::Packet& operator <<(sf::Packet& packet, const std::vector<Enity>& m)
{
	packet << m.size();
	for(std::size_t i = 0; i < m.size(); i++)
	{
		packet << m[i];
	}
	return packet;
}

sf::Packet& operator >>(sf::Packet& packet, std::vector<Enity>& m)
{
	std::size_t size;
	packet >> size;
	m.reserve(size);
	for(std::size_t i = 0; i < size; i++)
	{
		Enity temp;
		packet >> temp;
		m.push_back(temp);
	}
	return packet;
}
