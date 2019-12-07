#include "PlayingState.h"
#include "DeviceContext.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Events/ApplicationEvents.h"
#include "Events/AppEventQueue.h"

#ifdef QUARTZ_DEBUG
#include<iostream>
#endif

namespace Quartz
{
	void PlayingState::init(DeviceContext* dc)
	{
		if (m_Initialized)
			return;

		m_deviceContext = dc;
		m_renderWindow = m_deviceContext->m_Window->getRenderWindow();

		m_deviceContext->m_resourceManager->loadAudioFromFile("Playing/Audio.json");
		m_deviceContext->m_resourceManager->loadTexturesFromFile("Playing/Textures.json");
		m_deviceContext->m_resourceManager->loadSpritesFromFile("Playing/Sprites.json");


		m_deviceContext->m_resourceManager->loadTexture("REAPER_FALLING_SHEET", "C:\\Users\\rdpsi\\Downloads\\output-onlinepngtools.png");

		sf::Sprite sprite;
		sprite.setTexture(m_deviceContext->m_resourceManager->getTexture("REAPER_FALLING_SHEET"));
		sprite.setPosition(0.0f, 0.0f);
		sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));

		auto entity = std::make_unique<PlayerEntity>(m_deviceContext);

		entity->setSprite(sprite);

		anim.setSprite(entity->getSprite());
		anim.addFrame({ sf::IntRect(0, 0, 100, 100), 0.2f });
		anim.addFrame({ sf::IntRect(100, 0, 100, 100), 0.2f });
		anim.addFrame({ sf::IntRect(0, 100, 100, 100), 0.2f });
		anim.addFrame({ sf::IntRect(100, 100, 100, 100), 0.2f });
		anim.addFrame({ sf::IntRect(0, 200, 100, 100), 0.2f });
		anim.addFrame({ sf::IntRect(100, 200, 100, 100), 0.2f });


		m_Entities.push_back(std::move(entity));

		m_deviceContext->m_resourceManager->playMusic("PLAYING_AUDIO");

		m_Initialized = true;
	}

	void PlayingState::destroy()
	{
		// NOTHING FOR NOW
	}

	void PlayingState::paused()
	{
		// NOTHING FOR NOW
	}

	void PlayingState::resumed()
	{
		// NOTHING FOR NOW
	}

	void PlayingState::render()
	{
		m_renderWindow->draw(m_deviceContext->m_resourceManager->getSprite("PLAYING_SP"));

		for (auto& x : m_Entities)
			x->render();
	}

	void PlayingState::update(float dt)
	{
		anim.update(dt);
	}

	void PlayingState::handleInput(sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::KeyReleased:
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				AppEvent event;
				event.eventType = EventType::StateChangeEvent;
				event.m_Info.emplace<StateChangeEvent>("Paused");

				m_deviceContext->m_appEventQueue->addEventToQueue(event);
			}
		}
		}
	}

	bool PlayingState::isInitialized() const
	{
		return m_Initialized;
	}









}