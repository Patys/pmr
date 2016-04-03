#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Console
{
public:
	Console();
	void handleInput(sf::Event* event);
	std::string getLastCommand();
	std::string getLastParametr();
	void draw(sf::RenderWindow* window);
private:
	sf::RectangleShape console_background;
	std::vector<std::string> commands;
	std::string current_command;
};
