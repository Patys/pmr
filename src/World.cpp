#include "World.hpp"

void World::addEnity(Enity enity)
{
  enities.push_back(enity);
}

Enity* World::getEnity(const std::string& id)
{
  for(std::size_t i = 0; i < enities.size(); i++)
    {
      if(enities[i].id == id)
  	{
  	  return &enities[i];
  	}
    }
  return nullptr;
}

