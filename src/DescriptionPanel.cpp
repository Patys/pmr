#include "DescriptionPanel.hpp"
#include "Init.hpp"

void DescriptionPanel::update(sf::Event* event)
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

      if(event->type == sf::Event::KeyReleased)
	{
	  if(event->key.code == sf::Keyboard::Escape)
	    {
	      is_active = false;
	    }
	}
    }
}

void DescriptionPanel::draw(sf::RenderWindow* window)
{
  if(is_active)
    {
      sprites["gui_cross"].setPosition(100,45);
      sprites["gui_panel"].setPosition(75,20);
      window->draw(sprites["gui_panel"]);
      window->draw(sprites["gui_cross"]);
      sf::Text des_text(description.c_str(), font, 18);
      des_text.setPosition(100,100);
      window->draw(des_text);
    }
}
