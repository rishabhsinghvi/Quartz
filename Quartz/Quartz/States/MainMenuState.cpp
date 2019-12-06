#include "MainMenuState.h"
#include "ResourceManager.h"
#include "Window.h"
#include "UIButton.h"
#include "UIText.h"
#include "Application.h"
#include "Events/ApplicationEvents.h"

#include<iostream>
#include<unordered_map>

namespace Quartz
{
	
	void MainMenuState::init(DeviceContext* dc)
	{
		if (m_Initialized)
			return;


	
		m_deviceContext = dc;

		// Load Required Resources
		m_deviceContext->m_resourceManager->loadTexturesFromFile("MainMenu/Textures.json");
		m_deviceContext->m_resourceManager->loadSpritesFromFile("MainMenu/Sprites.json");
		m_deviceContext->m_resourceManager->loadAudioFromFile("MainMenu/Audio.json");

		m_renderWindow = m_deviceContext->m_Window->getRenderWindow();

		m_deviceContext->m_resourceManager->playMusic("SPLASH_AUDIO");


		// Create UI Elements
		auto title = std::make_unique<UIText>(0.35f, 0.15f, 2.5f, 2.5f, "Quartz");
		auto playButton = std::make_unique<UIButton>(0.48f, 0.5f, 0.5f, 0.5f, "Play");
		auto exitButton = std::make_unique<UIButton>(0.48f, 0.6f, 0.5f, 0.5f, "Exit");

		playButton->setCallback([](DeviceContext* dc)
			{
				AppEvent event;
				event.eventType = EventType::StateChangeEvent;
				event.m_Info.emplace<StateChangeEvent>("Playing");

				dc->m_appEventQueue->addEventToQueue(event);
			});

		exitButton->setCallback([](DeviceContext* dc)
			{
				AppEvent event;
				event.eventType = EventType::AppCloseEvent;

				dc->m_appEventQueue->addEventToQueue(event);
			});
		
		m_UIEntities.push_back(std::move(title));
		m_UIEntities.push_back(std::move(playButton));
		m_UIEntities.push_back(std::move(exitButton));


		m_Initialized = true;
	}

	void MainMenuState::destroy()
	{
		// NOTHING FOR NOW
		m_Initialized = false;
	}

	void MainMenuState::paused()
	{
		m_deviceContext->m_resourceManager->pauseMusic();
	}

	void MainMenuState::resumed()
	{
		// NOTHING FOR NOW
		m_deviceContext->m_resourceManager->resumeMusic();
	}

	void MainMenuState::render()
	{

		auto mousePos = sf::Mouse::getPosition(*m_renderWindow);



		m_renderWindow->draw(m_deviceContext->m_resourceManager->getSprite("SPLASH_SP"));
		for (auto& ui : m_UIEntities)
		{
			ui->onHover(mousePos.x, mousePos.y);
			m_renderWindow->draw(*ui);
		}
	}

	void MainMenuState::handleInput(sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonReleased:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				auto mousePos = sf::Mouse::getPosition(*m_renderWindow);

				// Change this
				/*if (m_UIEntities[2]->contains(mousePos.x, mousePos.y))
				{
					
					m_deviceContext->m_Application->setRunningState(false);
				}*/

				for (auto& x : m_UIEntities)
				{
					if (x->contains(mousePos.x, mousePos.y))
					{
						x->callback(m_deviceContext);
					}
				}
			}
			break;
		}

		case sf::Event::LostFocus:
		{
			paused();
			break;
		}

		case sf::Event::GainedFocus:
		{
			resumed();
			break;
		}

		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::A)
			{
				std::cout << "A\n";
			}
		}

		}
	}

	bool MainMenuState::isInitialized() const
	{
		return m_Initialized;
	}






}