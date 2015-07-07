#include "Game.hpp"
#include "Init.hpp"
#include "AssetsManager.hpp"
#include "EventManager.hpp"
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
	  if (event.type == sf::Event::Closed)
	    window.close();
	  if (event.type == sf::Event::LostFocus)
	    focused = false;
	  if (event.type == sf::Event::GainedFocus)
	    focused = true;
	  
	  sf::Vector2f world_pos = game_window.getCenter() - sf::Vector2f(400,300);
	  EventManager::update(&event, &world, world_pos, &client, &craft_panel, &description_panel);
	  description_panel.update(&event);
	  craft_panel.update(&event, &client);
        }
      
      if(focused)
	{
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	    client.sendCommand("player move", {"up", client.getPlayerID()});
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	    client.sendCommand("player move", {"down", client.getPlayerID()});
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	    client.sendCommand("player move", {"left", client.getPlayerID()});
	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	    client.sendCommand("player move", {"right", client.getPlayerID()});

	  if(sf::Mouse::getPosition(window).x > 795)
	    game_window.move(8,0);
	  if(sf::Mouse::getPosition(window).x < 5)
	    game_window.move(-8,0);
	  if(sf::Mouse::getPosition(window).y > 595)
	    game_window.move(0,8);
	  if(sf::Mouse::getPosition(window).y < 5)
	    game_window.move(0,-8);
	}

      if(description_panel.getActive() == true)
	{
	  auto item = world.getItem(EventManager::selected_world_item);
	  if(item)
	    description_panel.setDescription(getItemDescription(item->type));
	}

      client.update(&world);

      draw();
    }
}

void Game::draw()
{
  window.clear(sf::Color(100,150,40));

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

  if(EventManager::active_hand_menu)
    drawHandMenu();
  
  window.setView(window.getDefaultView());

  drawInventory();

  description_panel.draw(&window);
  craft_panel.draw(&window);

  sprites["gui_wrench"].setPosition(5, 5);
  window.draw(sprites["gui_wrench"]);

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
  if(world.getPlayer(client.getPlayerID()))
    for(auto x : world.getPlayer(client.getPlayerID())->inventory)
      {
	sprites[x.type].setPosition(pos.x * 65+80, 534);
	window.draw(sprites[x.type]);
      
	pos.x++;
      }
  select_inv_rect.setPosition(EventManager::selected_inventory_item * 65+80, 534);
  window.draw(select_inv_rect);
}

void Game::drawHandMenu()
{
  sprites["gui_cross"].setPosition(EventManager::position_hand_menu.x - 25, 
				   EventManager::position_hand_menu.y - 75);
  sprites["gui_info"].setPosition(EventManager::position_hand_menu.x + 25, 
				  EventManager::position_hand_menu.y - 25);
  sprites["gui_pick"].setPosition(EventManager::position_hand_menu.x - 75, 
				  EventManager::position_hand_menu.y - 25);

  window.draw(sprites["gui_cross"]);
  window.draw(sprites["gui_info"]);
  window.draw(sprites["gui_pick"]);
}

void Game::runClient(const std::string& ip)
{
  server_ip = ip;
  client.connect(server_ip);
  run();
}

void Game::runServer()
{
  server.setup();
  while(1)
    {
      server.update();
    }
}
