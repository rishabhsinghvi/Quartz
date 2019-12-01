#include "ResourceManager.h"

#include "JSON/json.hpp"

#include<iostream>
#include<fstream>

namespace Quartz
{
	extern const std::string CONFIG_DIRECTORY;
	extern const std::string TEXTURE_DIRECTORY;
	extern const std::string AUDIO_DIRECTORY;

	void ResourceManager::init()
	{
		// TODO
	}

	void ResourceManager::loadTexturesFromFile(const std::string & filePath)
	{
		using json = nlohmann::json;

		std::ifstream config(CONFIG_DIRECTORY + filePath);

		if (!config)
		{
			std::cout << "Unable to open config file: " << filePath << '\n';
			__debugbreak();
		}

		json root;
		config >> root;

		for (auto it = root.begin(); it != root.end(); it++)
		{
			loadTexture(it.key(), it.value());
			std::cout << "Loaded Texture: " << it.key() << '\n';
		}
	}

	void ResourceManager::loadSpritesFromFile(const std::string& filePath)
	{
		using json = nlohmann::json;

		std::ifstream config(CONFIG_DIRECTORY + filePath);

		if (!config)
		{
			std::cout << "Unable to open config file: " << filePath << '\n';
			__debugbreak();
		}

		json root;
		config >> root;

		for (auto it = root.begin(); it != root.end(); it++)
		{
			auto sprite = std::make_unique<sf::Sprite>();

			std::string spriteName = it.key();

			auto spriteConfig = it.value();
			auto& texture = getTexture(spriteConfig["TEXTURE_NAME"]);
			
			sprite->setTexture(texture);

			sprite->setScale(spriteConfig["SCALE_X"], spriteConfig["SCALE_Y"]);

			if (!spriteConfig["USE_FULL_TEXTURE"])
			{
				auto x = spriteConfig["X_COORD"];
				auto y = spriteConfig["Y_COORD"];
				auto w = spriteConfig["WIDTH"];
				auto h = spriteConfig["WIDTH"];
				sprite->setTextureRect(sf::IntRect(x, y, w, h));
			}
			
			loadSprite(spriteName, std::move(sprite));
			
			std::cout << "Loaded Sprite: " << spriteName << '\n';
		}
	}

	void ResourceManager::loadAudioFromFile(const std::string & filePath)
	{
		using json = nlohmann::json;

		std::ifstream config(CONFIG_DIRECTORY + filePath);

		if (!config)
		{
			std::cout << "Unable to open config file: " << filePath << '\n';
			__debugbreak();
		}

		json root;
		config >> root;

		for (auto it = root.begin(); it != root.end(); it++)
		{
			auto name = it.key();

			auto audioConfig = it.value();

			std::string audioFile = audioConfig["FILE_PATH"];

			if (audioConfig["STREAMABLE"])
			{
				m_musicDirectory[name] = std::move(audioFile);

				std::cout << "Loaded Audio: " << name << '\n';
				return;
			}

			loadSound(name, audioFile);

			std::cout << "Loaded Audio: " << name << '\n'; 
		}
	}

	void ResourceManager::loadTexture(const std::string & textureName, const std::string & texturePath)
	{
		auto inCache = m_textureCache.find(textureName);

		if (inCache != m_textureCache.end())
		{
			std::cout << "Texture: " << textureName << " already exists in texture cache. Replacing this texture...";
		}

		auto texture = std::make_unique<sf::Texture>();

		if (!texture->loadFromFile(texturePath))
		{
			__debugbreak();
		}

		m_textureCache[textureName] = std::move(texture);
	}

	void ResourceManager::loadTexture(const std::string & textureName, std::unique_ptr<sf::Texture> texture)
	{
		auto inCache = m_textureCache.find(textureName);

		if (inCache != m_textureCache.end())
		{
			std::cout << "Texture: " << textureName << " already exists in texture cache. Replacing this texture...\n";
		}

		m_textureCache[textureName] = std::move(texture);
	}

	void ResourceManager::loadSprite(const std::string & spriteName, std::unique_ptr<sf::Sprite> sprite)
	{
		auto inCache = m_spriteCache.find(spriteName);

		if (inCache != m_spriteCache.end())
		{
			std::cout << "Sprite : " << spriteName << " already exists in sprite cache. Replacing this sprite..\n";
		}

		m_spriteCache[spriteName] = std::move(sprite);

	}

	void ResourceManager::loadSound(const std::string & soundName, const std::string & soundPath)
	{
		auto inCache = m_soundCache.find(soundName);

		if (inCache != m_soundCache.end())
		{
			std::cout << "Sound : " << soundName << " already exists in sprite cache. Replacing this sound..\n";
		}

		auto soundBuffer = std::make_unique<sf::SoundBuffer>();

		if (!soundBuffer->loadFromFile(soundPath))
		{
			__debugbreak();
		}


		auto sound = std::make_unique<sf::Sound>();

		sound->setBuffer(*soundBuffer);

		m_soundBuffers.push_back(std::move(soundBuffer));
		m_soundCache[soundName] = std::move(sound);
	}

	void ResourceManager::loadSound(const std::string & soundName, std::unique_ptr<sf::Sound> sound)
	{
		auto inCache = m_soundCache.find(soundName);

		if (inCache != m_soundCache.end())
		{
			std::cout << "Sound : " << soundName << " already exists in sprite cache. Replacing this sound..\n";
		}

		m_soundCache[soundName] = std::move(sound);
	}

	const sf::Texture & ResourceManager::getTexture(const std::string & textureName) const
	{
		// TODO: Case insenstive lookup / hashing
		auto texture = m_textureCache.find(textureName);
		
		if (texture == m_textureCache.end())
		{
			std::cout << "Unable to retrieve texture: " << textureName << '\n';
			__debugbreak();
		}

		return *(texture->second);
	}

	const sf::Sprite & ResourceManager::getSprite(const std::string & spriteName) const
	{
		auto sprite = m_spriteCache.find(spriteName);

		if (sprite == m_spriteCache.end())
		{
			std::cout << "Unable to retrieve sprite: " << spriteName << '\n';
			__debugbreak();
		}

		return *(sprite->second);
	}

	const sf::Sound & ResourceManager::getSound(const std::string & soundName) const
	{
		auto sound = m_soundCache.find(soundName);

		if (sound == m_soundCache.end())
		{
			std::cout << "Unable to retrieve sound: " << soundName << '\n';
		}

		return *(sound->second);
	}

	void ResourceManager::playMusic(const std::string& soundName) const
	{
		auto sound = m_musicDirectory.find(soundName);

		if (sound == m_musicDirectory.end())
		{
			std::cout << "Unable to retrieve file: " << soundName << '\n';
			return;
		}

		sf::Music music;

		if (!music.openFromFile(sound->second))
		{
			std::cout << "Unable to open music file: " << sound->second << '\n';
		}

		music.setLoop(true);
		music.play();
	}



}