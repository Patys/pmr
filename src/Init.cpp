#include "Init.hpp"
#include "AssetsManager.hpp"

std::map<std::string, sf::Sprite> sprites;
sf::Font font;

void Init::init()
{
  font.loadFromFile("data/font/Roboto-Regular.ttf");

  Assets::Manager::loadTexture("player", "data/gfx/alienBeige.png");

  Assets::Manager::loadTexture("bush1", "data/gfx/rpgTile155.png");
  Assets::Manager::loadTexture("bush2", "data/gfx/rpgTile157.png");
  Assets::Manager::loadTexture("bush3", "data/gfx/rpgTile159.png");
  Assets::Manager::loadTexture("tree1", "data/gfx/tree.png");

  Assets::Manager::loadTexture("axe1", "data/gfx/axe.png");
  Assets::Manager::loadTexture("sword1", "data/gfx/sword.png");
  Assets::Manager::loadTexture("wood1", "data/gfx/wood.png");

  Assets::Manager::loadTexture("gui_inventory", "data/gfx/basket.png");
  Assets::Manager::loadTexture("gui_panel", "data/gfx/panel_gui.png");
  Assets::Manager::loadTexture("gui_cross", "data/gfx/cross.png");
  Assets::Manager::loadTexture("gui_info", "data/gfx/information.png");
  Assets::Manager::loadTexture("gui_wrench", "data/gfx/wrench.png");
  Assets::Manager::loadTexture("gui_pick", "data/gfx/export.png");

  sprites["player"] = sf::Sprite(*Assets::Manager::getTexture("player"));

  sprites["bush1"] = sf::Sprite(*Assets::Manager::getTexture("bush1"));
  sprites["bush2"] = sf::Sprite(*Assets::Manager::getTexture("bush2"));
  sprites["bush3"] = sf::Sprite(*Assets::Manager::getTexture("bush3"));
  sprites["tree1"] = sf::Sprite(*Assets::Manager::getTexture("tree1"));
  sprites["wood1"] = sf::Sprite(*Assets::Manager::getTexture("wood1"));

  sprites["axe1"] = sf::Sprite(*Assets::Manager::getTexture("axe1"));
  sprites["sword1"] = sf::Sprite(*Assets::Manager::getTexture("sword1"));

  sprites["gui_inventory"] = sf::Sprite(*Assets::Manager::getTexture("gui_inventory"));
  sprites["gui_panel"] = sf::Sprite(*Assets::Manager::getTexture("gui_panel"));
  sprites["gui_cross"] = sf::Sprite(*Assets::Manager::getTexture("gui_cross"));
  sprites["gui_info"] = sf::Sprite(*Assets::Manager::getTexture("gui_info"));
  sprites["gui_wrench"] = sf::Sprite(*Assets::Manager::getTexture("gui_wrench"));
  sprites["gui_pick"] = sf::Sprite(*Assets::Manager::getTexture("gui_pick"));
}
