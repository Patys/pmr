// 2014 (C) SAGE Engine
// Patryk Szczygło

#include "AssetsManager.hpp"
#include <iostream>

using namespace Assets;

std::map<std::string, std::shared_ptr<sf::Texture>> Manager::m_textures;
std::map<std::string, std::shared_ptr<sf::SoundBuffer>> Manager::m_soundbuffers;
std::map<std::string, std::shared_ptr<sf::Sound>> Manager::m_sounds;
std::map<std::string, std::unique_ptr<sf::Music>> Manager::m_musics;
std::map<std::string, std::shared_ptr<sf::Image>> Manager::m_images;

std::shared_ptr<sf::Texture> Manager::loadTexture(const std::string& id, const std::string& filepath)
{
  sf::Texture tex;
  if (tex.loadFromFile(filepath))
    {
      m_textures[id] = std::make_shared<sf::Texture>(tex);
      std::cout << "DEBUG_MESSAGE: " << filepath << " loading.\n";
      return m_textures[id];
    }

  // Texture not found, fill empty image
  std::cout << "Texture not found: " << filepath << std::endl;
  return nullptr;
}

std::shared_ptr<sf::Texture> Manager::getTexture(const std::string& id)
{
  // check, whether the id already exists
  for (auto it : m_textures)
    {
      if (id == it.first)
	{
	  return it.second;
	}
    }
	
  std::cout << "Texture not found ID: " << id << std::endl;
  return nullptr;
}

std::shared_ptr<sf::SoundBuffer> Manager::getSoundBuffer(const std::string& filepath)
{
  // check, whether the sound already exists
  for (auto& it : m_soundbuffers)
    {
      if (filepath == it.first)
	{
	  std::cout << "DEBUG_MESSAGE: " << filepath << " using existing soundbuffer.\n";
	  return it.second;
	}
    }

  // Sound doesn't exists
  sf::SoundBuffer sound;
  if (sound.loadFromFile(filepath))
    {
      m_soundbuffers[filepath] = std::make_shared<sf::SoundBuffer>(sound);
      std::cout << "DEBUG_MESSAGE: " << filepath << " loading soundbuffer.\n";
      return m_soundbuffers[filepath];
    }

  // Sound doesn't exists. Fill empty sound
  std::cout << "Sound not found: " << filepath << std::endl;
  return nullptr;
}

std::shared_ptr<sf::Sound> Manager::loadSound(const std::string& id, const std::string& filepath)
{
  sf::Sound sound;
	
  auto sound_buffer = Manager::getSoundBuffer(filepath);
	
  sound.setBuffer(*sound_buffer);
  m_sounds[id] = std::make_shared<sf::Sound>(sound);
	
  return m_sounds[id];
}

std::shared_ptr<sf::Sound> Manager::getSound(const std::string& id)
{
  // check, whether the sound already exists
  for (auto it : m_sounds)
    {
      if (id == it.first)
	{
	  return it.second;
	}
    }
	
  std::cout << "Sound not found ID: " << id << std::endl;
  return nullptr;
}

sf::Music& Manager::getMusic(const std::string& filepath)
{
  // check, whether the music already exists
  for (auto& it : m_musics)
    {
      if (filepath == it.first)
	{
	  std::cout << "DEBUG_MESSAGE: " << filepath << " using existing music.\n";
	  return *it.second;
	}
    }

  // Music doesn't exists
  auto music = std::make_unique<sf::Music>();
  if (music->openFromFile(filepath))
    {
      m_musics[filepath] = std::move(music);
      std::cout << "DEBUG_MESSAGE: " << filepath << " loading.\n";
      return *m_musics[filepath];
    }

  // Music doesn't exists. Fill empty music
  std::cout << "Music not found: " << filepath << std::endl;
  return *music;
}

std::shared_ptr<sf::Image> Manager::loadImage(const std::string& id, const std::string& filepath)
{
  // Image doesn't exists
  sf::Image img;
  if (img.loadFromFile(filepath))
    {
      m_images[id] = std::make_shared<sf::Image>(img);
      std::cout << "DEBUG_MESSAGE: " << filepath << " loading.\n";
      return m_images[id];
    }

  std::cout << "Music not found: " << filepath << std::endl;
  return nullptr;
}

std::shared_ptr<sf::Image> Manager::getImage(const std::string& id)
{
  // check, whether the image already exists
  for (auto it : m_images)
    {
      if (id == it.first)
	{
	  return it.second;
	}
    }

  std::cout << "Image not found: " << id << std::endl;
  return nullptr;
}
