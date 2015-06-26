#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class DescriptionPanel
{
public:

  DescriptionPanel() : is_active(false), description("") {}
  
  void update(sf::Event* event);

  void draw(sf::RenderWindow* window);

  bool getActive() { return is_active; }
  void setActive(bool active) { is_active = active; }

  const std::string& getDescription() { return description; }
  void setDescription(const std::string& new_description) { description = new_description.c_str(); }

private:
  bool is_active;
  std::string description;
};
