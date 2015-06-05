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
	      world->getPlayer(player_id)->inventory.push_back(Item(sf::Vector2f(0,0),
								    sf::Vector2f(34,34),
								    "item_02", "sword1"));
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
			      Player new_player;

			      if(packet >> new_player)
				{
				  world->getPlayer(new_player.id)->position.x = new_player.position.x;
				  world->getPlayer(new_player.id)->position.y = new_player.position.y;
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
