#include "Renderer.h"


namespace Quartz
{
	void Renderer::init(sf::RenderWindow* window, GameState gameState)
	{
		m_renderWindow = window;
		m_gameState = gameState;
	}

	void Renderer::setGameState(GameState gs)
	{
		m_gameState = gs;
	}

	void Renderer::setResourceManager(ResourceManager* rmanager)
	{
		m_resourceManager = rmanager;
	}

	void Renderer::render()
	{
		switch (m_gameState)
		{
		case GameState::SplashScreen:
			{

			m_renderWindow->draw(m_resourceManager->getSprite("SPLASH_SP"));
			
			break;
			}
		}
	}
	




}