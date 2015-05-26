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
	      world->addEnity(Enity(sf::Vector2f(100, 100),
	      			    sf::Vector2f(66, 92),
	       			    100, "player", player_id));
	      clients.push_back(client);
	      selector.add(*client);

	      sf::Packet start_packet;
	      start_packet << "new_client" << *world->getEnity(player_id); 
	      client->send(start_packet);
	      
	      std::cout << "New client.\n";
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
	  for(auto x : clients)
            {
	      sf::TcpSocket& client = *x;
	      if(selector.isReady(client))
                {
		  // The client has sent some data, we can receive it
		  sf::Packet packet;
		  if(client.receive(packet) == sf::Socket::Done)
                    {
		      std::string s;
		      packet >> s;
		      std::cout << s;
                    }
                }
            }
        }
    }
}
