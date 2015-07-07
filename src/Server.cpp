#include "Server.hpp"
#include <iostream>

Server::Server()
{

}

void Server::setup()
{
  listener.setBlocking(false);
  listener.listen(28282);
  selector.add(listener);

  world.addEnity(Enity(sf::Vector2f(300,300),
		       sf::Vector2f(64,64),
		       100, "bush1", "bush_01"));
  world.addEnity(Enity(sf::Vector2f(200,200),
		       sf::Vector2f(64,128),
		       100, "tree1", "tree_01"));
  world.addEnity(Enity(sf::Vector2f(250,300),
		       sf::Vector2f(64,128),
		       100, "tree1", "tree_02"));
  world.addEnity(Enity(sf::Vector2f(300,50),
		       sf::Vector2f(64,128),
		       100, "tree1", "tree_03"));
  world.addEnity(Enity(sf::Vector2f(400,100),
		       sf::Vector2f(64,128),
		       100, "tree1", "tree_05"));
  world.addEnity(Enity(sf::Vector2f(450,220),
		       sf::Vector2f(64,128),
		       100, "tree1", "tree_06"));
  world.addEnity(Enity(sf::Vector2f(500,180),
		       sf::Vector2f(64,128),
		       100, "tree1", "tree_07"));

  world.addItem(Item(sf::Vector2f(300,200),
		     sf::Vector2f(64,64),
		     "item_01", "axe1"));

  world.addItem(Item(sf::Vector2f(350,200),
		     sf::Vector2f(64,64),
		     "item_02", "sword1"));
}

void Server::update()
{
  if (selector.wait())
    {
      if (selector.isReady(listener))
        {
	  // The listener is ready: there is a pending connection
	  sf::TcpSocket* client = new sf::TcpSocket;
	  if (listener.accept(*client) == sf::Socket::Done)
            {
	      std::string player_id = "player_id__" + std::to_string(reinterpret_cast<uint32_t>(client));
	      
	      world.addPlayer(Player(player_id, 
				     sf::Vector2f(100, 100),
				     sf::Vector2f(66, 92), 100));
	      clients.push_back(client);
	      selector.add(*client);

	      sf::Packet start_packet;
	      start_packet << "connect" << player_id; 
	      client->send(start_packet);
	      
	      std::cout << "New client: " << client->getRemoteAddress().toString() << "\n";
            }
	  else
            {
	      // Error, we won't get a new connection, delete the socket
	      delete client;
            }
        }
      else
        {
	  // The listener socket is not ready, test all other sockets (the clients)
	  for(std::size_t x = 0; x < clients.size(); x++)
            {
	      sf::TcpSocket& client = *clients[x];
	      if(selector.isReady(client))
                {
		  // The client has sent some data, we can receive it
		  sf::Packet packet;
		  if(client.receive(packet) == sf::Socket::Done)
                    {
		      std::string event;
		      int num_data;
		      std::vector<std::string> data;
		      
		      if(packet >> event >> num_data)
			{
			  for(int i = 0; i < num_data; i++)
			    {
			      std::string temp_data;
			      packet >> temp_data;
			      data.push_back(temp_data);
			    }
			}
		      
		      excuteCommand(event, data, &client);
                    }
		  else if(client.receive(packet) == sf::Socket::Disconnected)
		    {
		      clients.erase(clients.begin() + x);
		      std::cout << "Disconnected\n";
		    }
		}
            }
        }
    }
}

void Server::excuteCommand(const std::string& command, std::vector<std::string> data, sf::TcpSocket* client)
{
  if(command == "player move")
    {
      std::string direction = data[0];
      std::string player_id = data[1];

      if(world.getPlayer(player_id))
	{
	  sf::Vector2f move;
	  if(data[0] == "up")
	    move = sf::Vector2f(0,-5);
	  if(data[0] == "down")
	    move = sf::Vector2f(0,5);
	  if(data[0] == "left")
	    move = sf::Vector2f(-5,0);
	  if(data[0] == "right")
	    move = sf::Vector2f(5,0);

	  sf::Vector2f new_player_position = world.getPlayer(player_id)->position + move;
	  sf::Vector2f player_size = world.getPlayer(player_id)->size;

	  bool make_move = true;
	  for(auto x : world.enities)
	    {
	      if(x.type == "tree1")
		{
		  if(new_player_position.x + player_size.x >= x.position.x && 
		     new_player_position.x <= x.position.x + x.size.x &&
		     new_player_position.y + player_size.y >= x.position.y && 
		     new_player_position.y <= x.position.y + x.size.y )
		    {
		      make_move = false;
		      break;
		    }
		}
	    }
	  if(make_move)
	    world.getPlayer(player_id)->position = new_player_position;
	}
    }

  if(command == "update world")
    {
      sf::Packet packet;
      packet << "update world" << world;
      client->send(packet);
    }

  if(command == "destroy item")
    {
      std::string item_id = data[0];
      world.removeItem(item_id);
    }

  if(command == "pick up")
    {
      std::string item_id = data[0];
      std::string player_id = data[1];

      auto player = world.getPlayer(player_id);
      if(player)
	{
	  if(player->inventory.size() <= 10)
	    {
	      auto item = world.getItem(item_id);
	      if(item)
		{
		  world.getPlayer(player_id)->inventory.push_back(*item);
		  world.removeItem(item_id);
		}
	    }
	}
    }

  if(command == "drop item")
    {
      std::string item_id = data[0];
      std::string player_id = data[1];

      auto player = world.getPlayer(player_id);
      if(player)
	{
	  Item item;
	  for(std::size_t i = 0; i < player->inventory.size(); i++)
	    {
	      if(player->inventory[i].id == item_id)
		{
		  item = player->inventory[i];
		  item.position = player->position;
		  world.addItem(item);
		  player->inventory.erase(player->inventory.begin() + i);
		}
	    }
	}
    }

  if(command == "attack enity")
    {
      std::string enity_id = data[0];
      
      auto enity = world.getEnity(enity_id);
      if(enity)
	{
	  enity->life -= 10;
	  if(enity->life <= 0)
	    {
	      if(enity->type == "tree1")
		{
		  Item item;
		  item.position = enity->position + sf::Vector2f(16,96);
		  item.size = sf::Vector2f(32,32);
		  item.id = "wood_" + std::to_string(reinterpret_cast<uint32_t>(enity));
		  item.type = "wood1";
		  world.addItem(item);
		}
	      world.removeEnity(enity_id);
	    }
	}
    }

  if(command == "craft item")
    {
      std::string item_pos = data[0];
      std::string player_id = data[1];

      int item_pos_inv = std::stoi(item_pos);
      auto player = world.getPlayer(player_id);
      
      if(player->inventory.size() >= item_pos_inv)
	{
	  if(player->inventory[item_pos_inv].type == "wood1")
	    {
	      std::string new_item_id = "item_" + std::to_string(reinterpret_cast<uint32_t>(&player->inventory[item_pos_inv]));
	      player->inventory.push_back(Item(sf::Vector2f(0,0),
					       sf::Vector2f(64,64),
					       new_item_id, "axe1"));
	      player->inventory.erase(item_pos_inv + player->inventory.begin());
	    }
	}
    }
}
