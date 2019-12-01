#include "MainMenuState.h"
#include "ResourceManager.h"
#include "Window.h"

namespace Quartz
{
	void MainMenuState::init(DeviceContext* dc)
	{
		if (m_Initialized)
			return;



		m_deviceContext = dc;

		m_deviceContext->m_resourceManager->loadTexturesFromFile("MainMenu/Textures.json");
		m_deviceContext->m_resourceManager->loadSpritesFromFile("MainMenu/Sprites.json");
		m_deviceContext->m_resourceManager->loadAudioFromFile("MainMenu/Audio.json");

		m_deviceContext->m_resourceManager->playMusic("SPLASH_AUDIO");

		m_Initialized = true;
	}

	void MainMenuState::destroy()
	{
		// NOTHING FOR NOW
		m_Initialized = false;
	}

	void MainMenuState::paused()
	{
		// NOTHING FOR NOW
	}

	void MainMenuState::resumed()
	{
		// NOTHING FOR NOW
	}

	void MainMenuState::render()
	{
		m_deviceContext->m_Window->getRenderWindow()->draw(m_deviceContext->m_resourceManager->getSprite("SPLASH_SP"));
	}

	void MainMenuState::handleInput(sf::Event& event)
	{

	}






}