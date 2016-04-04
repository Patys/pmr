#include "Console.hpp"
#include "Init.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

Console::Console()
{
	console_background.setPosition(0,0);
	console_background.setFillColor(sf::Color(0,0,0,128));
	console_background.setSize(sf::Vector2f(800, 400));
}

void Console::handleInput(sf::Event* event)
{
	if(event->type == sf::Event::KeyPressed)
	{
		if(event->key.code == sf::Keyboard::Return)
		{
			if(commands.size() > 30)
				commands.erase(commands.begin());
			commands.push_back(current_command);
			current_command = "";
		}
		if(event->key.code == sf::Keyboard::BackSpace && current_command.size()!=0)
		{
			current_command.pop_back();
		}
	}
	if(event->type == sf::Event::TextEntered)
	{
		if(event->text.unicode < 128 &&
			event->text.unicode != '\b' &&
			event->text.unicode != '\u000D') 
		{
			current_command += ((char)event->text.unicode);
		}
	}
}

std::string Console::getLastCommand()
{
	std::string command = commands.back();    
	std::vector<std::string> words;
	std::istringstream iss(command);

	std::copy(std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			std::back_inserter(words));
	return words.front();
}

std::string Console::getLastParametr()
{
	std::string command = commands.back();    
	std::vector<std::string> words;
	std::istringstream iss(command);

	std::copy(std::istream_iterator<std::string>(iss),
			std::istream_iterator<std::string>(),
			std::back_inserter(words));
	return words.back();
}

void Console::draw(sf::RenderWindow* window)
{
	window->draw(console_background);
	sf::Text text("", font);
	text.setCharacterSize(12);
	text.setPosition(0,0);
	for(auto x : commands)
	{
		text.setString(x);
		text.setPosition(0, text.getPosition().y + 12);
		window->draw(text);
	}
	text.setPosition(0, 387);
	text.setString(current_command);
	window->draw(text);
}
