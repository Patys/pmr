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
}

Game::~Game()
{
	
}

void Game::run()
{
  window.create(sf::VideoMode(800, 600), "Game by Patys");
  while(window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
        {
	  if (event.type == sf::Event::Closed)
	    window.close();
        }
        
      client.update(&world);

      draw();
    }
}

void Game::draw()
{
  window.clear();


  for(auto enity : world.getEnities())
    {
      drawEnity(enity.type, enity);
      window.draw(debug_text);
    }

  // TODO: create map sprites 
  // window.draw(sprite);

  window.display();
}

void Game::drawEnity(const std::string& spriteID, Enity& enity)
{
  sprites[spriteID].setPosition(enity.position);
  window.draw(sprites[spriteID]);

  debug_text.setPosition(enity.position.x, enity.position.y - 10);
  debug_text.setString(enity.id);
}

void Game::runClient(const std::string& ip)
{
  server_ip = ip;
  client.init(server_ip);
  run();
}

void Game::runServer()
{
  server.init();
  while(1)
    {
      server.update(&world);
    }
}
