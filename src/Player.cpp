#include "Player.hpp"

sf::Packet& operator <<(sf::Packet& packet, const Player& m)
{
	return packet << m.position.x << m.position.y << m.size.x << m.size.y << m.life << m.id << m.current_item << m.inventory;
}

sf::Packet& operator >>(sf::Packet& packet, Player& m)
{
	return packet >> m.position.x >> m.position.y >> m.size.x >> m.size.y >> m.life >> m.id >> m.current_item >> m.inventory;
}

sf::Packet& operator <<(sf::Packet& packet, const std::vector<Player>& m)
{
	packet << m.size();
	for(std::size_t i = 0; i < m.size(); i++)
	{
		packet << m[i];
	}
	return packet;
}

sf::Packet& operator >>(sf::Packet& packet, std::vector<Player>& m)
{
	std::size_t size;
	packet >> size;
	m.reserve(size);
	for(std::size_t i = 0; i < size; i++)
	{
		Player temp;
		packet >> temp;
		m.push_back(temp);
	}
	return packet;
}
