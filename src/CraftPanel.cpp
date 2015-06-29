#include "CraftPanel.hpp"
#include "EventManager.hpp"

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
      sf::Text des_text("Select item in inventory: 0-9\nIf you want to craft, press E\nPossible crafts:\nwood->axe", font, 14);
      des_text.setPosition(100,100);
      window->draw(des_text);
    }
}

void CraftPanel::update(sf::Event* event, Client* client)
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
	  if(event->key.code == sf::Keyboard::E)
	    {
	      client->runCommand("craft item", std::to_string(EventManager::selected_inventory_item));
	    }
	}
      
    }
}
