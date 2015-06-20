#include "EventManager.hpp"

std::string EventManager::selected_world_item = "";
int EventManager::selected_inventory_item = 0;
  
sf::Vector2f EventManager::position_hand_menu = sf::Vector2f(0,0);

bool EventManager::active_hand_menu = false;
bool EventManager::active_item_description = false;

void EventManager::update(sf::Event* event, World* world, sf::Vector2f view_position, Client* client)
{
  if(event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left)
    {
      sf::Vector2f mouse_pos = sf::Vector2f(event->mouseButton.x, event->mouseButton.y);

      if(!active_item_description)
	{
	  for(auto x : world->enities)
	    {
	      if(mouse_pos.x + view_position.x > x.position.x &&
		 mouse_pos.x + view_position.x < x.position.x + x.size.x &&
		 mouse_pos.y + view_position.y > x.position.y &&
		 mouse_pos.y + view_position.y < x.position.y + x.size.y)
		{
		  client->runCommand("attack enity", x.id);
		}
	    }

	  active_hand_menu = false;
	  for(auto x : world->items)
	    {
	      if(x.position.x < mouse_pos.x + view_position.x && 
		 x.position.x + x.size.x > mouse_pos.x + view_position.x &&
		 x.position.y < mouse_pos.y +view_position.y &&
		 x.position.y + x.size.y > mouse_pos.y + view_position.y)
		{
		  selected_world_item = x.id;
		  active_hand_menu = true;
		  position_hand_menu = mouse_pos + view_position;
		}
	    }
	}
    }

  
  if(event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
    {
      sf::Vector2f mouse_pos = sf::Vector2f(event->mouseButton.x, event->mouseButton.y);

      if(active_item_description)
	{
	  if(mouse_pos.x > 100 &&
	     mouse_pos.x < 150 &&
	     mouse_pos.y > 45 &&
	     mouse_pos.y < 95)
	    {
	      active_item_description = false;
	    }
	}
      if(active_hand_menu && !active_item_description)
	{
	  // click on cross
	  if(mouse_pos.x + view_position.x > position_hand_menu.x - 25 &&
	     mouse_pos.x + view_position.x < position_hand_menu.x + 25 &&
	     mouse_pos.y + view_position.y > position_hand_menu.y - 75 &&
	     mouse_pos.y + view_position.y < position_hand_menu.y - 25)
	    {
	      client->runCommand("destroy item", selected_world_item);
	      active_hand_menu = false;
	    }
	  // pick up
	  if(mouse_pos.x + view_position.x > position_hand_menu.x - 75 &&
	     mouse_pos.x + view_position.x < position_hand_menu.x - 25 &&
	     mouse_pos.y + view_position.y > position_hand_menu.y - 25 &&
	     mouse_pos.y + view_position.y < position_hand_menu.y + 25)
	    {
	      client->runCommand("pick up", selected_world_item);
	      active_hand_menu = false;
	    }
	  // info
	  if(mouse_pos.x + view_position.x > position_hand_menu.x + 25 &&
	     mouse_pos.x + view_position.x < position_hand_menu.x + 75 &&
	     mouse_pos.y + view_position.y > position_hand_menu.y - 25 &&
	     mouse_pos.y + view_position.y < position_hand_menu.y + 75)
	    {
	      active_item_description = true;
	      active_hand_menu = false;
	    }
	}
    }

  if(event->type == sf::Event::KeyReleased)
    {
      if(!active_item_description)
	{
	  if(event->key.code == sf::Keyboard::Q)
	    {
	      if(selected_inventory_item < world->getPlayer(client->getPlayerID())->inventory.size())
		{
		  Item item = world->getPlayer(client->getPlayerID())->inventory[selected_inventory_item];
		  client->runCommand("drop item", item.id);
		}
	    }
	}
      if(event->key.code == sf::Keyboard::Escape)
	{
	  active_item_description = false;
	}

      if(event->key.code == sf::Keyboard::Num1)
	selected_inventory_item = 0;
      if(event->key.code == sf::Keyboard::Num2)
	selected_inventory_item = 1;
      if(event->key.code == sf::Keyboard::Num3)
	selected_inventory_item = 2;
      if(event->key.code == sf::Keyboard::Num4)
	selected_inventory_item = 3;
      if(event->key.code == sf::Keyboard::Num5)
	selected_inventory_item = 4;
      if(event->key.code == sf::Keyboard::Num6)
	selected_inventory_item = 5;
      if(event->key.code == sf::Keyboard::Num7)
	selected_inventory_item = 6;
      if(event->key.code == sf::Keyboard::Num8)
	selected_inventory_item = 7;
      if(event->key.code == sf::Keyboard::Num9)
	selected_inventory_item = 8;
      if(event->key.code == sf::Keyboard::Num0)
	selected_inventory_item = 9;
    }

}
