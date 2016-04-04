#include "Game.hpp"
#include "Init.hpp"
#include "AssetsManager.hpp"
#include <iostream>

Game::Game()
{
	selected_world_item = "";
	selected_inventory_item = 0;
	position_hand_menu = sf::Vector2f(0, 0);
	active_hand_menu = false;
	active_console = true;
}

Game::~Game()
{
	
}

void Game::init()
{
	Init::init();

	debug_text.setFont(font);
	debug_text.setCharacterSize(10);

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
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Tab)
				{
					active_console = !active_console;
				}
			}
			if(active_console)
				console.handleInput(&event);
			
			handleInput(&event);
			description_panel.update(&event);
			craft_panel.update(&event, selected_inventory_item);
		}
      
		if(focused)
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				Client::sendCommand("player move", {"up", Client::getPlayerID()});
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				Client::sendCommand("player move", {"down", Client::getPlayerID()});
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				Client::sendCommand("player move", {"left", Client::getPlayerID()});
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				Client::sendCommand("player move", {"right", Client::getPlayerID()});

			if(sf::Mouse::getPosition(window).x > 795)
				game_window.move(8,0);
			if(sf::Mouse::getPosition(window).x < 5)
				game_window.move(-8,0);
			if(sf::Mouse::getPosition(window).y > 595)
				game_window.move(0,8);
			if(sf::Mouse::getPosition(window).y < 5)
				game_window.move(0,-8);
		}

		if(description_panel.getActive() == true)
		{
			auto item = world.getEnity(selected_world_item);
			if(item)
				description_panel.setDescription(getItemDescription(item->type));
		}

		Client::update(&world);

		draw();
	}
}

void Game::handleInput(sf::Event* event)
{
	sf::Vector2f view_position = game_window.getCenter() - sf::Vector2f(400,300);
	  
	if(event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left)
    {
		sf::Vector2f mouse_pos = sf::Vector2f(event->mouseButton.x, event->mouseButton.y);

		if(description_panel.getActive() == false)
		{
			for(auto x : world.enities)
			{
				if(mouse_pos.x + view_position.x > x.position.x &&
					mouse_pos.x + view_position.x < x.position.x + x.size.x &&
					mouse_pos.y + view_position.y > x.position.y &&
					mouse_pos.y + view_position.y < x.position.y + x.size.y)
				{
					if(x.attackable)
						Client::sendCommand("attack enity", {x.id});
				}
			}

			active_hand_menu = false;
			for(auto x : world.enities)
			{
				if(x.position.x < mouse_pos.x + view_position.x && 
					x.position.x + x.size.x > mouse_pos.x + view_position.x &&
					x.position.y < mouse_pos.y +view_position.y &&
					x.position.y + x.size.y > mouse_pos.y + view_position.y)
				{
					if(x.attackable == false)
					{
						selected_world_item = x.id;
						active_hand_menu = true;
						position_hand_menu = mouse_pos + view_position;
					}
				}
			}
			// craft
			if(mouse_pos.x > 5 &&
				mouse_pos.x < 55 &&
				mouse_pos.y > 5 &&
				mouse_pos.y < 55)
			{
				craft_panel.setActive(true);
			}
		}
	}

  
	if(event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left)
    {
		sf::Vector2f mouse_pos = sf::Vector2f(event->mouseButton.x, event->mouseButton.y);

		if(active_hand_menu)
		{
			// click on cross
			if(mouse_pos.x + view_position.x > position_hand_menu.x - 25 &&
				mouse_pos.x + view_position.x < position_hand_menu.x + 25 &&
				mouse_pos.y + view_position.y > position_hand_menu.y - 75 &&
				mouse_pos.y + view_position.y < position_hand_menu.y - 25)
			{
				Client::sendCommand("destroy item", {selected_world_item});
				active_hand_menu = false;
			}
			// pick up
			if(mouse_pos.x + view_position.x > position_hand_menu.x - 75 &&
				mouse_pos.x + view_position.x < position_hand_menu.x - 25 &&
				mouse_pos.y + view_position.y > position_hand_menu.y - 25 &&
				mouse_pos.y + view_position.y < position_hand_menu.y + 25)
			{
				Client::sendCommand("pick up", {selected_world_item, Client::getPlayerID()});
				active_hand_menu = false;
			}
			// info
			if(mouse_pos.x + view_position.x > position_hand_menu.x + 25 &&
				mouse_pos.x + view_position.x < position_hand_menu.x + 75 &&
				mouse_pos.y + view_position.y > position_hand_menu.y - 25 &&
				mouse_pos.y + view_position.y < position_hand_menu.y + 75)
			{
				description_panel.setActive(true);
				active_hand_menu = false;
			}
		}
	}

	if(event->type == sf::Event::KeyReleased)
	{
		if(event->key.code == sf::Keyboard::Q)
		{
			if(selected_inventory_item < world.getPlayer(Client::getPlayerID())->inventory.size())
			{
				Enity item = world.getPlayer(Client::getPlayerID())->inventory[selected_inventory_item];
				Client::sendCommand("drop item", {item.id, Client::getPlayerID()});
			}
		}

		if(event->key.code == sf::Keyboard::Num1)
			selected_inventory_item = 0;
		if(event->key.code == sf::Keyboard::Num2)
			selected_inventory_item = 1;
		if(event->key.code == sf::Keyboard::Num3)
			selected_inventory_item = 2;
		if(event->key.code == sf::Keyboard::Num4)
			selected_inventory_item = 3;
		if(event->key.code == sf::Keyboard::Num5)
			selected_inventory_item = 4;
		if(event->key.code == sf::Keyboard::Num6)
			selected_inventory_item = 5;
		if(event->key.code == sf::Keyboard::Num7)
			selected_inventory_item = 6;
		if(event->key.code == sf::Keyboard::Num8)
			selected_inventory_item = 7;
		if(event->key.code == sf::Keyboard::Num9)
			selected_inventory_item = 8;
		if(event->key.code == sf::Keyboard::Num0)
			selected_inventory_item = 9;
    }
}

void Game::draw()
{
	window.clear(sf::Color(100,150,40));

	window.setView(game_window);

	for(auto _enity : world.enities)
	{
		drawEnity(_enity.type, _enity);
		window.draw(debug_text);
	}

	for(auto _player : world.players)
	{
		drawPlayer("player", _player);
		window.draw(debug_text);
	}

	if(active_hand_menu)
		drawHandMenu();

	window.setView(window.getDefaultView());

	drawInventory();

	description_panel.draw(&window);
	craft_panel.draw(&window);

	sprites["gui_wrench"].setPosition(5, 5);
	window.draw(sprites["gui_wrench"]);

	if(active_console)
		console.draw(&window);
	window.display();
}

void Game::drawEnity(const std::string& spriteID, Enity& enity)
{
	sprites[spriteID].setPosition(enity.position);
	window.draw(sprites[spriteID]);

	debug_text.setPosition(enity.position.x, enity.position.y - 10);
	debug_text.setString(enity.id);
}

void Game::drawPlayer(const std::string& spriteID, Player& player)
{
	sprites[spriteID].setPosition(player.position);
	window.draw(sprites[spriteID]);

	debug_text.setPosition(player.position.x, player.position.y - 10);
	debug_text.setString(player.id);
}

void Game::drawInventory()
{
	sf::RectangleShape inv_rect(sf::Vector2f(64,64));
	inv_rect.setFillColor(sf::Color::Transparent);
	inv_rect.setOutlineThickness(2);
	inv_rect.setOutlineColor(sf::Color::White);

	sf::RectangleShape select_inv_rect(sf::Vector2f(64,64));
	select_inv_rect.setFillColor(sf::Color::Transparent);
	select_inv_rect.setOutlineThickness(2);
	select_inv_rect.setOutlineColor(sf::Color::Green);
	sf::Vector2f pos(0,0);

	for(std::size_t i = 0; i < 10; i++)
	{
		inv_rect.setPosition(pos.x * 65+80, 534);
		window.draw(inv_rect);
		pos.x++;
	}
	pos.x = 0;
	if(world.getPlayer(Client::getPlayerID()))
	for(auto x : world.getPlayer(Client::getPlayerID())->inventory)
	{
		sprites[x.type].setPosition(pos.x * 65+80, 534);
		window.draw(sprites[x.type]);

		pos.x++;
	}
	select_inv_rect.setPosition(selected_inventory_item * 65+80, 534);
	window.draw(select_inv_rect);
}

void Game::drawHandMenu()
{
	sprites["gui_cross"].setPosition(position_hand_menu.x - 25, 
										position_hand_menu.y - 75);
	sprites["gui_info"].setPosition(position_hand_menu.x + 25, 
										position_hand_menu.y - 25);
	sprites["gui_pick"].setPosition(position_hand_menu.x - 75, 
										position_hand_menu.y - 25);

	window.draw(sprites["gui_cross"]);
	window.draw(sprites["gui_info"]);
	window.draw(sprites["gui_pick"]);
}

void Game::runClient(const std::string& ip)
{
	server_ip = ip;
	Client::connect(server_ip);
	run();
}

void Game::runServer()
{
	server.setup();
	while(1)
	{
		server.update();
	}
}
