#pragma once

#include <string>
#include <SFML/Graphics.hpp>

struct Enity
{

  Enity(sf::Vector2f pos, sf::Vector2f _size, int _life, std::string _type, std::string _id):
    position(pos), size(_size), life(_life), type(_type), id(_id) {}

  sf::Vector2f position;
  sf::Vector2f size;

  // life inform us when destroy enity
  int life;

  std::string type;
  std::string id;
};
