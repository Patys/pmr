#include "CraftPanel.hpp"

CraftPanel::CraftPanel() : 
  is_active(false)
{

}

void CraftPanel::draw(sf::RenderWindow* window)
{
  if(is_active)
    {
      sprites["gui_cross"].setPosition(100,45);
      sprites["gui_panel"].setPosition(75,20);
      window->draw(sprites["gui_panel"]);
      window->draw(sprites["gui_cross"]);

    }
}

void CraftPanel::update(sf::Event* event)
{
  if(is_active)
    {
      if(event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
	{
	  sf::Vector2f mouse_pos = sf::Vector2f(event->mouseButton.x, event->mouseButton.y);

	  if(mouse_pos.x > 100 &&
	     mouse_pos.x < 150 &&
	     mouse_pos.y > 45 &&
	     mouse_pos.y < 95)
	    {
	      is_active = false;
	    }
	}
    }
}
