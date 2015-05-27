#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Enity.hpp"

class World
{
public:
  
  void addEnity(Enity enity);
  Enity* getEnity(const std::string& id);

  inline const std::vector<Enity> getEnities() { return enities; }
  inline void changeWorld(std::vector<Enity> ens) { enities.clear(); enities.swap(ens); }

private:
  std::vector<Enity> enities;
};
