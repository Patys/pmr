#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "Client.hpp"
#include "Server.hpp"
#include "World.hpp"
#include "CraftPanel.hpp"
#include "DescriptionPanel.hpp"

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

  void drawGUI();
  void drawInventory();
  void drawHandMenu();

  void drawItemDescription(const std::string& description);
  
  CraftPanel craft_panel;
  DescriptionPanel description_panel;

  World world;
  sf::Text debug_text;
	
  Client client;
  Server server;

  std::string server_ip;
  std::string player_id;
	
  sf::RenderWindow window;
  sf::View game_window;
};
