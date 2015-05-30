#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "Client.hpp"
#include "Server.hpp"
#include "World.hpp"

class Game
{
public:
  Game();
  ~Game();
	
  void runClient(const std::string& ip);
  void runServer();
private:
  void init();

  void run();

  void draw();
  void drawEnity(const std::string& spriteID, Enity& enity);
  void drawItem(const std::string& spriteID, Item& item);
  void drawPlayer(const std::string& spriteID, Player& player);

  World world;
  sf::Font font;
  sf::Text debug_text;
  std::map<std::string, sf::Sprite> sprites;
	
  Client client;
  Server server;
	
  std::string server_ip;
	
  sf::RenderWindow window;
  sf::View game_window;
};
