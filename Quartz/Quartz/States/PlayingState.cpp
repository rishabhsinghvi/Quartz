#include "PlayingState.h"
#include "DeviceContext.h"
#include "ResourceManager.h"
#include "Events/ApplicationEvents.h"
#include "Events/AppEventQueue.h"
#include "Entity/MoveableEntity.h"
#include "Entity/Player.h"
#include "Logger/Logger.h"

#ifdef QUARTZ_DEBUG
#include<iostream>
#endif

namespace Quartz
{
	extern const unsigned int WINDOW_WIDTH;
	extern const unsigned int WINDOW_HEIGHT;


	void PlayingState::init(DeviceContext* dc)
	{
		if (m_Initialized)
			return;

		m_deviceContext = dc;

		m_Physics = std::make_unique<PhysicsEngine>();


		// Load data persistent with all levels
		m_deviceContext->m_resourceManager->loadAudioFromFile("Playing/Audio.json");
		m_deviceContext->m_resourceManager->loadTexturesFromFile("Playing/Textures.json");
		m_deviceContext->m_resourceManager->loadSpritesFromFile("Playing/Sprites.json");


		// Create level 
		createLevel("Level1");

		// Start level audio; should probably change this if/when different levels have different audio
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
		m_currentLevel->render();
		/*m_renderWindow->draw(m_deviceContext->m_resourceManager->getSprite("PLAYING_SP"));

		m_tileMap.render();

		for (auto& x : m_Entities)
			x->render();*/
	}

	void PlayingState::update(float dt)
	{
		m_currentLevel->update(dt);
		m_Physics->update(dt);
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

	void PlayingState::createLevel(const std::string& levelName)
	{
		m_currentLevel.reset();
		m_currentLevel = std::make_unique<Level>(levelName, m_deviceContext);

		m_Physics->clearEngine();

		// Register All Entities
		for (const auto& entity : m_currentLevel->getEntityList())
		{
			m_Physics->registerEntity(entity.get());
		}


		// Register Tilemap (for Collision Detection)

		m_Physics->registerTileMap(m_currentLevel->getTileMap().get());
		

	}









}