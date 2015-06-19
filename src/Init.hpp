#pragma once 

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#define NETWORK_PORT 28282

extern std::map<std::string, sf::Sprite> sprites;
extern sf::Font font;

namespace Init
{
  void init();
}
