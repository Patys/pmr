// 2014 (C) SAGE Engine
// Patryk Szczygło
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <memory>

namespace Assets
{
  class Manager
  {
  public:
    static std::shared_ptr<sf::Texture> loadTexture(const std::string& id, const std::string& filepath);
    static std::shared_ptr<sf::Texture> getTexture(const std::string& id);
		
    static std::shared_ptr<sf::Image> loadImage(const std::string& id, const std::string& filepath);
    static std::shared_ptr<sf::Image> getImage(const std::string& id);
		
    static std::shared_ptr<sf::Sound> loadSound(const std::string& id, const std::string& filepath);
    static std::shared_ptr<sf::Sound> getSound(const std::string& id);
		
    static std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string& filepath);
		
    static sf::Music& getMusic(const std::string& filepath);
		
  private:
    static std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
    static std::map<std::string, std::shared_ptr<sf::SoundBuffer>> m_soundbuffers;
    static std::map<std::string, std::shared_ptr<sf::Sound>> m_sounds;
    static std::map<std::string, std::unique_ptr<sf::Music>> m_musics;
    static std::map<std::string, std::shared_ptr<sf::Image>> m_images;
  };
}

