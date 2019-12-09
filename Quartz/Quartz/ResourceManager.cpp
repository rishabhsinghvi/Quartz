#include "ResourceManager.h"
#include "Logger/Logger.h"

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
			LOG_ERROR("Unable to open config file: {0}", filePath);
		}

		json root;
		config >> root;

		for (auto it = root.begin(); it != root.end(); it++)
		{
			loadTexture(it.key(), it.value());
		}
	}

	void ResourceManager::loadSpritesFromFile(const std::string& filePath)
	{
		using json = nlohmann::json;

		std::ifstream config(CONFIG_DIRECTORY + filePath);

		if (!config)
		{
			LOG_ERROR("Unable to open config file: {0}", filePath);
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
			
			LOG_INFO("Loaded Sprite: {0}", spriteName);
		}
	}

	void ResourceManager::loadAudioFromFile(const std::string & filePath)
	{
		using json = nlohmann::json;

		std::ifstream config(CONFIG_DIRECTORY + filePath);

		if (!config)
		{
			LOG_ERROR("Unable to open config file: {0}", filePath);
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

				LOG_INFO("ResourceManager: Loaded Audio: {0}", name);
				return;
			}

			loadSound(name, audioFile);

			LOG_INFO("ResourceManager: Loaded Audio: {0}", name);
		}
	}

	void ResourceManager::loadTexture(const std::string & textureName, const std::string & texturePath)
	{
		auto inCache = m_textureCache.find(textureName);

		if (inCache != m_textureCache.end())
		{
			LOG_WARN("ResourceManager: Texture {0} already exists in texture cache. Replacing this texture...", textureName);
		}

		auto texture = std::make_unique<sf::Texture>();

		if (!texture->loadFromFile(texturePath))
		{
			__debugbreak();
		}

		m_textureCache[textureName] = std::move(texture);
		LOG_INFO("ResourceManager: Texture loaded: {0}", textureName);
	}

	void ResourceManager::loadTexture(const std::string & textureName, std::unique_ptr<sf::Texture> texture)
	{
		auto inCache = m_textureCache.find(textureName);

		if (inCache != m_textureCache.end())
		{
			LOG_WARN("ResourceManager: Texture {0} already exists in texture cache. Replacing this texture...", textureName);
		}

		m_textureCache[textureName] = std::move(texture);
		LOG_INFO("ResourceManager: Texture loaded: {0}", textureName);
	}

	void ResourceManager::loadSprite(const std::string & spriteName, std::unique_ptr<sf::Sprite> sprite)
	{
		auto inCache = m_spriteCache.find(spriteName);

		if (inCache != m_spriteCache.end())
		{
			LOG_WARN("ResourceManager: Sprite {0} already exists in sprite cache. Replacing this sprite...", spriteName);
		}

		m_spriteCache[spriteName] = std::move(sprite);
		LOG_INFO("ResourceManager: Loaded Sprite: {0}", spriteName);

	}

	void ResourceManager::loadSound(const std::string & soundName, const std::string & soundPath)
	{
		auto inCache = m_soundCache.find(soundName);

		if (inCache != m_soundCache.end())
		{
			LOG_WARN("ResourceManager: Sound {0} already exists in sound cache. Replacing this sound...", soundName);
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
			LOG_WARN("ResourceManager: Sound {0} already exists in sound cache. Replacing this sound...", soundName);
		}

		m_soundCache[soundName] = std::move(sound);
	}

	const sf::Texture & ResourceManager::getTexture(const std::string & textureName) const
	{
		// TODO: Case insenstive lookup / hashing
		auto texture = m_textureCache.find(textureName);
		
		if (texture == m_textureCache.end())
		{
			LOG_ERROR("ResourceManager: Unable to retrieve texture: {0}", textureName);
			__debugbreak();
		}

		return *(texture->second);
	}

	sf::Texture* ResourceManager::getTexturePointer(const std::string& textureName) const
	{
		auto texture = m_textureCache.find(textureName);

		if (texture == m_textureCache.end())
		{
			LOG_ERROR("ResourceManager: Unable to retrieve texture: {0}", textureName);
			__debugbreak();
		}

		return texture->second.get();
	}

	sf::Sprite ResourceManager::getSprite(const std::string & spriteName) const
	{
		auto sprite = m_spriteCache.find(spriteName);

		if (sprite == m_spriteCache.end())
		{
			LOG_ERROR("ResourceManager: Unable to retrieve sprite: {0}", spriteName);
			__debugbreak();
		}

		return *(sprite->second);
	}

	const sf::Sprite& ResourceManager::getSpriteRef(const std::string& spriteName) const
	{
		auto sprite = m_spriteCache.find(spriteName);

		if (sprite == m_spriteCache.end())
		{
			LOG_ERROR("ResourceManager: Unable to retrieve sprite: {0}", spriteName);
			__debugbreak();
		}

		return *(sprite->second);
	}

	const sf::Sound & ResourceManager::getSound(const std::string & soundName) const
	{
		auto sound = m_soundCache.find(soundName);

		if (sound == m_soundCache.end())
		{
			LOG_ERROR("ResourceManager: Unable to retrieve sound: {0}", soundName);
		}

		return *(sound->second);
	}

	void ResourceManager::playMusic(const std::string& soundName)
	{
		auto sound = m_musicDirectory.find(soundName);

		if (sound == m_musicDirectory.end())
		{
			LOG_ERROR("ResourceManager: Unable to retrieve file: {0}", soundName);
			return;
		}

		if (!m_currentMusic.openFromFile(sound->second))
		{
			LOG_ERROR("ResourceManager: Unable to retrieve sound: {0}", sound->second);
		}

		m_currentMusic.setLoop(true);
		m_currentMusic.play();
	}

	void ResourceManager::pauseMusic()
	{
		m_currentMusic.pause();
	}

	void ResourceManager::resumeMusic()
	{
		m_currentMusic.play();
	}



}