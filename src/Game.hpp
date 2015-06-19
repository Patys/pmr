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

  void drawGUI();
  void drawInventory();
  void drawHandMenu();

  void drawItemDescription(const std::string& description);
  bool draw_item_description;

  int selected_item_in_inventory;

  bool hand_menu_active;
  sf::Vector2f position_hand_menu;
  std::string selected_item_in_world;

  World world;
  sf::Text debug_text;
	
  Client client;
  Server server;

  std::string server_ip;
  std::string player_id;
	
  sf::RenderWindow window;
  sf::View game_window;
};
