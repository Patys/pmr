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
  Assets::Manager::loadTexture("gui_panel", "data/gfx/panel_gui.png");
  Assets::Manager::loadTexture("gui_cross", "data/gfx/cross.png");
  Assets::Manager::loadTexture("gui_info", "data/gfx/information.png");
  Assets::Manager::loadTexture("gui_wrench", "data/gfx/wrench.png");
  Assets::Manager::loadTexture("gui_pick", "data/gfx/export.png");

  sprites["player"] = sf::Sprite(*Assets::Manager::getTexture("player"));

  sprites["bush1"] = sf::Sprite(*Assets::Manager::getTexture("bush1"));
  sprites["bush2"] = sf::Sprite(*Assets::Manager::getTexture("bush2"));
  sprites["bush3"] = sf::Sprite(*Assets::Manager::getTexture("bush3"));
  sprites["tree1"] = sf::Sprite(*Assets::Manager::getTexture("tree1"));

  sprites["axe1"] = sf::Sprite(*Assets::Manager::getTexture("axe1"));
  sprites["sword1"] = sf::Sprite(*Assets::Manager::getTexture("sword1"));

  sprites["gui_inventory"] = sf::Sprite(*Assets::Manager::getTexture("gui_inventory"));
  sprites["gui_panel"] = sf::Sprite(*Assets::Manager::getTexture("gui_panel"));
  sprites["gui_cross"] = sf::Sprite(*Assets::Manager::getTexture("gui_cross"));
  sprites["gui_info"] = sf::Sprite(*Assets::Manager::getTexture("gui_info"));
  sprites["gui_wrench"] = sf::Sprite(*Assets::Manager::getTexture("gui_wrench"));
  sprites["gui_pick"] = sf::Sprite(*Assets::Manager::getTexture("gui_pick"));

  draw_inventory = false;
  draw_hand_menu = false;

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
	      sf::Vector2f mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(window);
	      sf::Vector2f world_pos = game_window.getCenter() - sf::Vector2f(400,300);

	      if(mouse_pos.x > 750 && mouse_pos.x < 800 &&
		 mouse_pos.y > 550 && mouse_pos.y < 600)
		{
		  draw_inventory = !draw_inventory;
		}

	      if(draw_hand_menu)
		{
		  // click on cross
		  if(mouse_pos.x + world_pos.x > position_hand_menu.x - 32 &&
		     mouse_pos.x + world_pos.x < position_hand_menu.x &&
		     mouse_pos.y + world_pos.y > position_hand_menu.y - 64 &&
		     mouse_pos.y + world_pos.y < position_hand_menu.y)
		    {
		      client.runCommand("destroy item", selected_item);
		    }
		  // pick up
		  if(mouse_pos.x + world_pos.x > position_hand_menu.x - 64 &&
		     mouse_pos.x + world_pos.x < position_hand_menu.x &&
		     mouse_pos.y + world_pos.y > position_hand_menu.y - 32 &&
		     mouse_pos.y + world_pos.y < position_hand_menu.y)
		    {
		      client.runCommand("pick up", selected_item);
		    }
		}

	      draw_hand_menu = false;
	      for(auto x : world.items)
		{
		  if(x.position.x < mouse_pos.x + world_pos.x && 
		     x.position.x + x.size.x > mouse_pos.x + world_pos.x &&
		     x.position.y < mouse_pos.y + world_pos.y &&
		     x.position.y + x.size.y > mouse_pos.y + world_pos.y)
		    {
		      selected_item = x.id;
		      draw_hand_menu = !draw_hand_menu;
		      position_hand_menu = mouse_pos + world_pos;
		    }
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

  if(draw_hand_menu)
    drawHandMenu();

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
  sprites["gui_panel"].setPosition(100,100);
  window.draw(sprites["gui_panel"]);

  sf::RectangleShape inv_rect(sf::Vector2f(64,64));
  inv_rect.setFillColor(sf::Color::Transparent);
  inv_rect.setOutlineThickness(2);
  inv_rect.setOutlineColor(sf::Color::White);
  sf::Vector2f pos(0,0);

  for(std::size_t i = 0; i < 40; i++)
    {
      inv_rect.setPosition(pos.x * 67 + 135, pos.y * 67 + 150);
      window.draw(inv_rect);
      pos.x++;
      if(pos.x >= 8)
	{
	  pos.x = 0;
	  pos.y++;
	}
    }
  pos.x = 0;
  pos.y = 0;
  for(auto x : world.getPlayer(player_id)->inventory)
    {
      sprites[x.type].setPosition(pos.x * 67 + 135, pos.y * 67 + 150);
      window.draw(sprites[x.type]);
      
      pos.x++;
      if(pos.x > 8)
	{
	  pos.x = 0;
	  pos.y++;
	}
    }
}

void Game::drawHandMenu()
{
  sprites["gui_cross"].setPosition(position_hand_menu.x - 32, position_hand_menu.y - 64);
  sprites["gui_info"].setPosition(position_hand_menu.x - 32, position_hand_menu.y);
  sprites["gui_pick"].setPosition(position_hand_menu.x - 64, position_hand_menu.y-32);
  sprites["gui_wrench"].setPosition(position_hand_menu.x, position_hand_menu.y-32);

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


void setupWorld(World* world)
{
  world->addEnity(Enity(sf::Vector2f(100,150),
			sf::Vector2f(64,64),
			100, "bush1", "bush_01"));
  world->addEnity(Enity(sf::Vector2f(200,200),
			sf::Vector2f(64,128),
			100, "tree1", "tree_01"));

  world->addItem(Item(sf::Vector2f(300,200),
		      sf::Vector2f(64,64),
		      "item_01", "axe1"));

  world->addItem(Item(sf::Vector2f(350,200),
		      sf::Vector2f(64,64),
		      "item_02", "sword1"));
  
}
