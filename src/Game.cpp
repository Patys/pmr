#include "Game.hpp"
#include "AssetsManager.hpp"
#include <iostream>


Game::Game()
{
  font.loadFromFile("data/font/Roboto-Regular.ttf");

  debug_text.setFont(font);
  debug_text.setCharacterSize(10);

  Assets::Manager::loadTexture("player", "data/gfx/alienBeige.png");
  Assets::Manager::loadTexture("barrel", "data/gfx/rpgTile204.png");
  Assets::Manager::loadTexture("bush1", "data/gfx/rpgTile155.png");
  Assets::Manager::loadTexture("bush2", "data/gfx/rpgTile157.png");
  Assets::Manager::loadTexture("bush3", "data/gfx/rpgTile159.png");

  sprites["player"] = sf::Sprite(*Assets::Manager::getTexture("player"));
  sprites["barrel"] = sf::Sprite(*Assets::Manager::getTexture("barrel"));
  sprites["bush1"] = sf::Sprite(*Assets::Manager::getTexture("bush1"));
  sprites["bush2"] = sf::Sprite(*Assets::Manager::getTexture("bush2"));
  sprites["bush3"] = sf::Sprite(*Assets::Manager::getTexture("bush3"));

  game_window.reset(sf::FloatRect(-100, -100, 800, 600));
}

Game::~Game()
{
	
}

void Game::run()
{
  window.create(sf::VideoMode(800, 600), "Game by Patys");
  window.setFramerateLimit(60);
  bool focused = true;
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
        }
      
      if(focused)
	{
	  if(sf::Mouse::getPosition(window).x > 790)
	    game_window.move(8,0);
	  if(sf::Mouse::getPosition(window).x < 10)
	    game_window.move(-8,0);
	  if(sf::Mouse::getPosition(window).y > 590)
	    game_window.move(0,8);
	  if(sf::Mouse::getPosition(window).y < 10)
	    game_window.move(0,-8);

	  client.update(&world);
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

  window.setView(window.getDefaultView());

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

void Game::runClient(const std::string& ip)
{
  server_ip = ip;
  client.init(server_ip);
  run();
}

void Game::runServer()
{
  world.addEnity(Enity(sf::Vector2f(100,150),
		       sf::Vector2f(64,64),
		       100, "bush1", "bush_01"));
  server.init();
  while(1)
    {
      server.update(&world);
    }
}
