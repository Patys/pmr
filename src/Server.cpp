#include "Server.hpp"
#include <iostream>

Server::Server()
{
	
}

Server::~Server()
{
	
}

void Server::init()
{
  listener.setBlocking(false);
  listener.listen(28282);
  selector.add(listener);
}

void Server::update(World* world)
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
	      world->addPlayer(Player(player_id, 
				      sf::Vector2f(100, 100),
				      sf::Vector2f(66, 92), 100));
	      clients.push_back(client);
	      selector.add(*client);

	      sf::Packet start_packet;
	      start_packet << "connect" << *world->getPlayer(player_id); 
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
		      
		      if(packet >> event)
			{
			  if(event == "player move")
			    {
			      std::string player_id;
			      std::string direction;
			      if(packet >> direction >> player_id)
				{
				  sf::Vector2f move;
				  if(direction == "up")
				    move = sf::Vector2f(0,-5);
				  if(direction == "down")
				    move = sf::Vector2f(0,5);
				  if(direction == "left")
				    move = sf::Vector2f(-5,0);
				  if(direction == "right")
				    move = sf::Vector2f(5,0);

				  sf::Vector2f new_player_position = world->getPlayer(player_id)->position + move;
				  sf::Vector2f player_size = world->getPlayer(player_id)->size;
				  bool make_move = true;
				  for(auto x : world->enities)
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
				    world->getPlayer(player_id)->position = new_player_position;
				}
			    }
			  if(event == "update world")
			    {
			      sf::Packet send_packet;
			      send_packet << "update world" << *world;
			      client.send(send_packet);
			    }
			  if(event == "destroy item")
			    {
			      std::string item_id;
			      
			      if(packet >> item_id)
				{
				  world->removeItem(item_id);
				}
			    }
			  if(event == "pick up")
			    {
			      std::string item_id;
			      std::string player_id;
			      
			      if(packet >> item_id >> player_id)
				{
				  auto _player = world->getPlayer(player_id);
				  if(_player)
				    {
				      if(_player->inventory.size() <= 10)
					{
					  auto item = world->getItem(item_id);
					  if(item)
					    {
					      world->getPlayer(player_id)->inventory.push_back(*item);
					      world->removeItem(item_id);
					    }
					}
				    }
				}
			    }
			  if(event == "drop item")
			    {
			      std::string item_id;
			      std::string player_id;
			      
			      if(packet >> item_id >> player_id)
				{
				  auto _player = world->getPlayer(player_id);
				  if(_player)
				    {
				      Item item;
				      for(std::size_t i = 0; i < _player->inventory.size(); i++)
					{
					  if(_player->inventory[i].id == item_id)
					    {
					      item = _player->inventory[i];
					      item.position = _player->position;
					      world->addItem(item);
					      _player->inventory.erase(_player->inventory.begin() + i);
					    }
				        }
				    }
				}
			    }
			  if(event == "attack enity")
			    {
			      std::string enity_id;
			      
			      if(packet >> enity_id)
				{
				  auto enity = world->getEnity(enity_id);
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
					      world->addItem(item);
					    }
					  world->removeEnity(enity_id);
					}
				    }
				}
			    }
			  if(event == "craft item")
			    {
			      std::string item_pos;
			      std::string player_id;
			      if(packet >> item_pos >> player_id)
				{
				  int item_pos_inv = std::stoi(item_pos);
				  auto player = world->getPlayer(player_id);
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
			}
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
