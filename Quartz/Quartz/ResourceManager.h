#ifndef QUARTZ_RESOURCE_MANAGER_H
#define QUARTZ_RESOURCE_MANAGER_H

#include<unordered_map>
#include<memory>
#include<string>
#include<vector>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

namespace Quartz
{
	class ResourceManager
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textureCache;
		std::unordered_map<std::string, std::unique_ptr<sf::Sprite>> m_spriteCache;
		std::unordered_map<std::string, std::unique_ptr<sf::Sound>> m_soundCache;

		std::unordered_map<std::string, std::string> m_musicDirectory;
		
		std::vector<std::unique_ptr<sf::SoundBuffer>> m_soundBuffers; // Need to do this so that SoundBuffer aren't deleted

		sf::Music m_currentMusic;

	public:

		void init();

		void loadTexturesFromFile(const std::string& filePath);
		
		void loadSpritesFromFile(const std::string& filePath);

		void loadAudioFromFile(const std::string& filePath);

		void loadTexture(const std::string& textureName, const std::string& texturePath);

		void loadTexture(const std::string& textureName, std::unique_ptr<sf::Texture> texture);

		void loadSprite(const std::string& textureName, std::unique_ptr<sf::Sprite> sprite);

		void loadSound(const std::string& soundName, const std::string& soundPath);

		void loadSound(const std::string& soundName, std::unique_ptr<sf::Sound> sound);


		const sf::Texture& getTexture(const std::string& textureName) const;

		sf::Texture* getTexturePointer(const std::string& textureName) const;

		const sf::Sprite& getSprite(const std::string& spriteName) const;

		const sf::Sound& getSound(const std::string& soundName) const;

		void playMusic(const std::string& soundName);

		void pauseMusic();

		void resumeMusic();
	};
}

#endif