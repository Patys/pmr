#include "Game.hpp"
#include "Init.hpp"
#include "AssetsManager.hpp"
#include <iostream>

Game::Game()
{

}

Game::~Game()
{
	
}

void Game::init()
{
  Init::init();

  debug_text.setFont(font);
  debug_text.setCharacterSize(10);

  hand_menu_active = false;
  draw_item_description = false;
  selected_item_in_inventory = 0;
  
  game_window.reset(sf::FloatRect(-100, -100, 800, 600));
}

void Game::run()
{
  window.create(sf::VideoMode(800, 600), "Game by Patys");
  window.setFramerateLimit(60);
  bool focused = true;

  init();

  while(window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
        {
	  sf::Vector2f mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(window);
	  sf::Vector2f world_pos = game_window.getCenter() - sf::Vector2f(400,300);

	  if (event.type == sf::Event::Closed)
	    window.close();
	  if (event.type == sf::Event::LostFocus)
	    focused = false;
	  if (event.type == sf::Event::GainedFocus)
	    focused = true;
	  if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	    {
	      if(!draw_item_description)
		{
		  for(auto x : world.enities)
		    {
		      if(mouse_pos.x + world_pos.x > x.position.x &&
			 mouse_pos.x + world_pos.x < x.position.x + x.size.x &&
			 mouse_pos.y + world_pos.y > x.position.y &&
			 mouse_pos.y + world_pos.y < x.position.y + x.size.y)
			{
			  client.runCommand("attack enity", x.id);
			}
		    }

		  hand_menu_active = false;
		  for(auto x : world.items)
		    {
		      if(x.position.x < mouse_pos.x + world_pos.x && 
			 x.position.x + x.size.x > mouse_pos.x + world_pos.x &&
			 x.position.y < mouse_pos.y + world_pos.y &&
			 x.position.y + x.size.y > mouse_pos.y + world_pos.y)
			{
			  selected_item_in_world = x.id;
			  hand_menu_active = true;
			  position_hand_menu = mouse_pos + world_pos;
			}
		    }
		}
		
	    } 
	  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	    {
	      if(draw_item_description)
		{
		  if(mouse_pos.x > 100 &&
		     mouse_pos.x < 150 &&
		     mouse_pos.y > 45 &&
		     mouse_pos.y < 95)
		    {
		      draw_item_description = false;
		    }
		}
	      if(hand_menu_active && !draw_item_description)
		{
		  // click on cross
		  if(mouse_pos.x + world_pos.x > position_hand_menu.x - 25 &&
		     mouse_pos.x + world_pos.x < position_hand_menu.x + 25 &&
		     mouse_pos.y + world_pos.y > position_hand_menu.y - 75 &&
		     mouse_pos.y + world_pos.y < position_hand_menu.y - 25)
		    {
		      client.runCommand("destroy item", selected_item_in_world);
		      hand_menu_active = false;
		    }
		  // pick up
		  if(mouse_pos.x + world_pos.x > position_hand_menu.x - 75 &&
		     mouse_pos.x + world_pos.x < position_hand_menu.x - 25 &&
		     mouse_pos.y + world_pos.y > position_hand_menu.y - 25 &&
		     mouse_pos.y + world_pos.y < position_hand_menu.y + 25)
		    {
		      client.runCommand("pick up", selected_item_in_world);
		      hand_menu_active = false;
		    }
		  // info
		  if(mouse_pos.x + world_pos.x > position_hand_menu.x + 25 &&
		     mouse_pos.x + world_pos.x < position_hand_menu.x + 75 &&
		     mouse_pos.y + world_pos.y > position_hand_menu.y - 25 &&
		     mouse_pos.y + world_pos.y < position_hand_menu.y + 75)
		    {
		      draw_item_description = true;
		      hand_menu_active = false;
		    }
		}
	    }
	  if (event.type == sf::Event::KeyReleased)
	    {
	      if(!draw_item_description)
		{
		  if(event.key.code == sf::Keyboard::Q)
		    {
		      if(selected_item_in_inventory < world.getPlayer(player_id)->inventory.size())
			{
			  Item item = world.getPlayer(player_id)->inventory[selected_item_in_inventory];
			  client.runCommand("drop item", item.id);
			}
		    }
		}
	      if(event.key.code == sf::Keyboard::Escape)
		{
		  draw_item_description = false;
		}
	    }
	 
        }
      
      if(focused)
	{
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	    selected_item_in_inventory = 0;
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	    selected_item_in_inventory = 1;
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	    selected_item_in_inventory = 2;
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	    selected_item_in_inventory = 3;
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	    selected_item_in_inventory = 4;
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	    selected_item_in_inventory = 5;
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	    selected_item_in_inventory = 6;
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	    selected_item_in_inventory = 7;
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
	    selected_item_in_inventory = 8;
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
	    selected_item_in_inventory = 9;

	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	    client.runCommand("player move", "up");
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	    client.runCommand("player move", "down");
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	    client.runCommand("player move", "left");
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	    client.runCommand("player move", "right");

	  if(sf::Mouse::getPosition(window).x > 795)
	    game_window.move(8,0);
	  if(sf::Mouse::getPosition(window).x < 5)
	    game_window.move(-8,0);
	  if(sf::Mouse::getPosition(window).y > 595)
	    game_window.move(0,8);
	  if(sf::Mouse::getPosition(window).y < 5)
	    game_window.move(0,-8);

	  client.update(&world, player_id);
	}

      draw();
    }
}

void Game::draw()
{
  window.clear();

  window.setView(game_window);

  for(auto _enity : world.enities)
    {
      drawEnity(_enity.type, _enity);
      window.draw(debug_text);
    }

  for(auto _item : world.items)
    {
      drawItem(_item.type, _item);
      window.draw(debug_text);
    }

  for(auto _player : world.players)
    {
      drawPlayer("player", _player);
      window.draw(debug_text);
    }

  if(hand_menu_active)
    drawHandMenu();

  window.setView(window.getDefaultView());
  
  drawInventory();
  if(draw_item_description)
    {
      auto item = world.getItem(selected_item_in_world);
      if(item)
	drawItemDescription(getItemDescription(item->type));
    }
  window.display();
}

void Game::drawEnity(const std::string& spriteID, Enity& enity)
{
  sprites[spriteID].setPosition(enity.position);
  window.draw(sprites[spriteID]);

  debug_text.setPosition(enity.position.x, enity.position.y - 10);
  debug_text.setString(enity.id);
}

void Game::drawItem(const std::string& spriteID, Item& item)
{
  sprites[spriteID].setPosition(item.position);
  window.draw(sprites[spriteID]);

  debug_text.setPosition(item.position.x, item.position.y - 10);
  debug_text.setString(item.id);
}

void Game::drawPlayer(const std::string& spriteID, Player& player)
{
  sprites[spriteID].setPosition(player.position);
  window.draw(sprites[spriteID]);

  debug_text.setPosition(player.position.x, player.position.y - 10);
  debug_text.setString(player.id);
}

void Game::drawGUI()
{

}

void Game::drawInventory()
{
  sf::RectangleShape inv_rect(sf::Vector2f(64,64));
  inv_rect.setFillColor(sf::Color::Transparent);
  inv_rect.setOutlineThickness(2);
  inv_rect.setOutlineColor(sf::Color::White);

  sf::RectangleShape select_inv_rect(sf::Vector2f(64,64));
  select_inv_rect.setFillColor(sf::Color::Transparent);
  select_inv_rect.setOutlineThickness(2);
  select_inv_rect.setOutlineColor(sf::Color::Green);
  sf::Vector2f pos(0,0);

  for(std::size_t i = 0; i < 10; i++)
    {
      inv_rect.setPosition(pos.x * 65+80, 534);
      window.draw(inv_rect);
      pos.x++;
    }
  pos.x = 0;
  for(auto x : world.getPlayer(player_id)->inventory)
    {
      sprites[x.type].setPosition(pos.x * 65+80, 534);
      window.draw(sprites[x.type]);
      
      pos.x++;
    }
  select_inv_rect.setPosition(selected_item_in_inventory * 65+80, 534);
  window.draw(select_inv_rect);
}

void Game::drawItemDescription(const std::string& description)
{
  sprites["gui_cross"].setPosition(100,45);
  sprites["gui_panel"].setPosition(75,20);
  window.draw(sprites["gui_panel"]);
  window.draw(sprites["gui_cross"]);
  sf::Text des_text(description.c_str(), font, 18);
  des_text.setPosition(100,100);
  window.draw(des_text);
}

void Game::drawHandMenu()
{
  sprites["gui_cross"].setPosition(position_hand_menu.x - 25, position_hand_menu.y - 75);
  sprites["gui_info"].setPosition(position_hand_menu.x + 25, position_hand_menu.y - 25);
  sprites["gui_pick"].setPosition(position_hand_menu.x - 75, position_hand_menu.y - 25);
  sprites["gui_wrench"].setPosition(position_hand_menu.x - 25, position_hand_menu.y + 25);

  window.draw(sprites["gui_cross"]);
  window.draw(sprites["gui_info"]);
  window.draw(sprites["gui_pick"]);
  window.draw(sprites["gui_wrench"]);
}

void Game::runClient(const std::string& ip)
{
  server_ip = ip;
  client.init(server_ip);
  run();
}

void Game::runServer()
{
  setupWorld(&world);

  server.init();
  while(1)
    {
      server.update(&world);
    }
}
