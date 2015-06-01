#include "Game.hpp"
#include "AssetsManager.hpp"
#include <iostream>

void setupWorld(World* world);

Game::Game()
{

}

Game::~Game()
{
	
}

void Game::init()
{
  font.loadFromFile("data/font/Roboto-Regular.ttf");

  debug_text.setFont(font);
  debug_text.setCharacterSize(10);

  Assets::Manager::loadTexture("player", "data/gfx/alienBeige.png");

  Assets::Manager::loadTexture("bush1", "data/gfx/rpgTile155.png");
  Assets::Manager::loadTexture("bush2", "data/gfx/rpgTile157.png");
  Assets::Manager::loadTexture("bush3", "data/gfx/rpgTile159.png");
  Assets::Manager::loadTexture("tree1", "data/gfx/tree.png");

  Assets::Manager::loadTexture("axe1", "data/gfx/axe.png");
  Assets::Manager::loadTexture("sword1", "data/gfx/sword.png");

  Assets::Manager::loadTexture("gui_inventory", "data/gfx/basket.png");
  Assets::Manager::loadTexture("gui_panel", "data/gfx/panel_brown.png");

  sprites["player"] = sf::Sprite(*Assets::Manager::getTexture("player"));

  sprites["bush1"] = sf::Sprite(*Assets::Manager::getTexture("bush1"));
  sprites["bush2"] = sf::Sprite(*Assets::Manager::getTexture("bush2"));
  sprites["bush3"] = sf::Sprite(*Assets::Manager::getTexture("bush3"));
  sprites["tree1"] = sf::Sprite(*Assets::Manager::getTexture("tree1"));

  sprites["axe1"] = sf::Sprite(*Assets::Manager::getTexture("axe1"));
  sprites["sword1"] = sf::Sprite(*Assets::Manager::getTexture("sword1"));

  sprites["gui_inventory"] = sf::Sprite(*Assets::Manager::getTexture("gui_inventory"));
  sprites["gui_panel"] = sf::Sprite(*Assets::Manager::getTexture("gui_panel"));

  draw_inventory = false;

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
	  if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	    {
	      if(event.mouseButton.x > 750 && event.mouseButton.x < 800 &&
		 event.mouseButton.y > 550 && event.mouseButton.y < 600)
		{
		  draw_inventory = !draw_inventory;
		}
	    }
        }
      
      if(focused)
	{
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

  window.setView(window.getDefaultView());
  
  drawGUI();
  if(draw_inventory)
    drawInventory();

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
  sprites["gui_inventory"].setPosition(750,550);
  window.draw(sprites["gui_inventory"]);
}

void Game::drawInventory()
{
  sprites["gui_panel"].setScale(6,4);
  sprites["gui_panel"].setPosition(100,100);
  window.draw(sprites["gui_panel"]);

  sf::Vector2f pos(0,0);
  for(auto x : world.getPlayer(player_id)->inventory)
    {
      sprites[x.type].setPosition(pos.x * 36 + 130, pos.y * 36 + 150);
      window.draw(sprites[x.type]);
      
      pos.x++;
      if(pos.x > 8)
	{
	  pos.x = 0;
	  pos.y++;
	}
    }
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


void setupWorld(World* world)
{
  world->addEnity(Enity(sf::Vector2f(100,150),
			sf::Vector2f(64,64),
			100, "bush1", "bush_01"));
  world->addEnity(Enity(sf::Vector2f(200,200),
			sf::Vector2f(64,128),
			100, "tree1", "tree_01"));

  world->addItem(Item(sf::Vector2f(300,200),
		      sf::Vector2f(34,34),
		      "item_01", "axe1"));

  world->addItem(Item(sf::Vector2f(350,200),
		      sf::Vector2f(34,34),
		      "item_02", "sword1"));
  
}
