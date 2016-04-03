#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "Client.hpp"
#include "Server.hpp"
#include "World.hpp"
#include "CraftPanel.hpp"
#include "DescriptionPanel.hpp"
#include "Console.hpp"

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

	void handleInput(sf::Event* event);

	void draw();
	void drawEnity(const std::string& spriteID, Enity& enity);
	void drawPlayer(const std::string& spriteID, Player& player);

	void drawGUI();
	void drawInventory();
	void drawHandMenu();

	void drawItemDescription(const std::string& description);

	CraftPanel craft_panel;
	DescriptionPanel description_panel;

	World world;
	sf::Text debug_text;

	Console console;

	// gui events 
	std::string selected_world_item;
	int selected_inventory_item;

	sf::Vector2f position_hand_menu;
	bool active_hand_menu;
	
	bool active_console;
	//

	Client client;
	Server server;

	std::string server_ip;

	sf::RenderWindow window;
	sf::View game_window;
};
