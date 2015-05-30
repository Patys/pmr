#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>

class Item
{
public:
  Item() {}
  Item(sf::Vector2f pos, sf::Vector2f _size, std::string _id, std::string _type):
    position(pos), size(_size), id(_id), type(_type) {}

  sf::Vector2f position; // on map
  sf::Vector2f size;

  std::string id;
  std::string type;

};

sf::Packet& operator <<(sf::Packet& packet, const Item& m);
sf::Packet& operator >>(sf::Packet& packet, Item& m);

sf::Packet& operator <<(sf::Packet& packet, const std::vector<Item>& m);
sf::Packet& operator >>(sf::Packet& packet, std::vector<Item>& m);
