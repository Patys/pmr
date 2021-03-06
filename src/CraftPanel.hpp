#pragma once

#include <SFML/Graphics.hpp>
#include "Init.hpp"
#include "Client.hpp"

class CraftPanel
{
public:
	CraftPanel();

	void draw(sf::RenderWindow* window);
	void update(sf::Event* event, int selected_inventory_item);

	bool getActive() { return is_active; }
	void setActive(bool active) { is_active = active; }

private:
	bool is_active;
  
};
