#pragma once

#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "Client.hpp"

namespace EventManager
{
  extern std::string selected_world_item;
  extern int selected_inventory_item;
  
  extern sf::Vector2f position_hand_menu;

  extern bool active_hand_menu;
  extern bool active_item_description;

  void update(sf::Event* event, World* world, sf::Vector2f view_position, Client* client);
}
