#include "MainMenuState.h"
#include "ResourceManager.h"
#include "Window.h"
#include "UIButton.h"
#include "UIText.h"

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

		m_renderWindow = m_deviceContext->m_Window->getRenderWindow();

		m_deviceContext->m_resourceManager->playMusic("SPLASH_AUDIO");

		// Create UI Elements

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
		UIText title(700.f, 180.f, 2.5f, 2.5f, "Quartz");
		UIButton playButton(900.0f, 550.0f, 0.5f, 0.5f, "Play");
		auto mousePos = sf::Mouse::getPosition(*m_renderWindow);

		playButton.onHover(mousePos.x, mousePos.y);
		m_renderWindow->draw(m_deviceContext->m_resourceManager->getSprite("SPLASH_SP"));
		m_renderWindow->draw(title);
		m_renderWindow->draw(playButton);
	}

	void MainMenuState::handleInput(sf::Event& event)
	{

	}






}