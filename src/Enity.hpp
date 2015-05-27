#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

struct Enity
{
  Enity() : 
    position(0,0), size(0,0), life(0), type("none"), id("none") {}
  Enity(sf::Vector2f pos, sf::Vector2f _size, int _life, const std::string& _type, const std::string& _id):
    position(pos), size(_size), life(_life), type(_type), id(_id) {}

  sf::Vector2f position;
  sf::Vector2f size;

  // life inform us when destroy enity
  int life;

  std::string type;
  std::string id;
};


sf::Packet& operator <<(sf::Packet& packet, const Enity& m);
sf::Packet& operator >>(sf::Packet& packet, Enity& m);

sf::Packet& operator <<(sf::Packet& packet, const std::vector<Enity>& m);
sf::Packet& operator >>(sf::Packet& packet, std::vector<Enity>& m);
