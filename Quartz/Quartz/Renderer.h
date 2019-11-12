#ifndef QUARTZ_RENDERER_H
#define QUARTZ_RENDERER_H

#include<memory>

#include "ResourceManager.h"
#include "GameState.h"

#include "SFML/Graphics.hpp"

namespace Quartz
{
	class Renderer
	{
	private:
		sf::RenderWindow* m_renderWindow = nullptr;
		GameState m_gameState;

		ResourceManager* m_resourceManager;

	public:
		void init(sf::RenderWindow* window, GameState gameState = GameState::SplashScreen);

		void setGameState(GameState gs);

		void setResourceManager(ResourceManager* rmanager);

		void render();
	};
}

#endif