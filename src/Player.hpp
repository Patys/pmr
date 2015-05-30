#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include "Item.hpp"

class Player
{
public:
  Player() {}
  Player(std::string _id, sf::Vector2f pos, sf::Vector2f _size, int _life):
    id(_id), position(pos), size(_size), life(_life) {}

  std::string id;

  sf::Vector2f position;
  sf::Vector2f size;
  
  int life;
  
  std::string current_item; // type of item
  std::vector<Item> inventory;
};


sf::Packet& operator <<(sf::Packet& packet, const Player& m);
sf::Packet& operator >>(sf::Packet& packet, Player& m);

sf::Packet& operator <<(sf::Packet& packet, const std::vector<Player>& m);
sf::Packet& operator >>(sf::Packet& packet, std::vector<Player>& m);
