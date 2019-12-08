#include "PlayingState.h"
#include "DeviceContext.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Events/ApplicationEvents.h"
#include "Events/AppEventQueue.h"
#include "Entity/MoveableEntity.h"

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


		// Create sprite to hold texture when paused
		auto tempSprite = std::make_unique<sf::Sprite>();




		m_deviceContext->m_resourceManager->loadTexture("REAPER_WALKING_RIGHT", "C:\\Users\\rdpsi\\Downloads\\Reaper_Walking_SS_100_Right.png");
		m_deviceContext->m_resourceManager->loadTexture("REAPER_WALKING_LEFT", "C:\\Users\\rdpsi\\Downloads\\Reaper_Walking_SS_100_Left.png");
		m_deviceContext->m_resourceManager->loadTexture("REAPER_SLASHING_RIGHT", "C:\\Users\\rdpsi\\Downloads\\Reaper_Slashing_SS_100_Right.png");
		sf::Sprite sprite;
		sprite.setTexture(m_deviceContext->m_resourceManager->getTexture("REAPER_WALKING_RIGHT"));
		sprite.setPosition(0.0f, 0.0f);
		sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));

		auto entity = std::make_unique<MoveableEntity>(m_deviceContext);
		entity->setSprite(sprite);
		entity->setVelocity(Vec2(100.0f, 0.0f));

		entity->createAnimationList("Reaper.json");
		entity->setAnimation("WALKING_RIGHT");

		/*anim.setSprite(entity->getSprite());
		anim.addFrame({ sf::IntRect(0, 0, 100, 100), 0.05f });
		anim.addFrame({ sf::IntRect(0, 101, 100,100), 0.05f });
		anim.addFrame({ sf::IntRect(101,0,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(101,101,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(0,202,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(101,202,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(202,0,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(202,101,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(202,202,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(0,303,100,100), 0.05f });

		anim.addFrame({ sf::IntRect(101,303,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(202,303,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(303,0,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(303,101,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(303,202,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(303,303,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(0,404,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(101,404,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(202,404,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(303,404,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(404,0,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(404,101,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(404,202,100,100), 0.05f });
		anim.addFrame({ sf::IntRect(404,303,100,100), 0.05f });

*/


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
		for (auto& x : m_Entities)
		{
			x->update(dt);
		}
		
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