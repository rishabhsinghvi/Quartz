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
		//m_renderWindow = m_deviceContext->m_Window->getRenderWindow();

		m_Physics = std::make_unique<PhysicsEngine>();

		m_deviceContext->m_resourceManager->loadAudioFromFile("Playing/Audio.json");
		m_deviceContext->m_resourceManager->loadTexturesFromFile("Playing/Textures.json");
		m_deviceContext->m_resourceManager->loadSpritesFromFile("Playing/Sprites.json");

		//m_currentLevel = std::make_unique<Level>("Level1", m_deviceContext);

		createLevel("Level1");


		// Create sprite to hold texture when paused
		/*auto tempSprite = std::make_unique<sf::Sprite>();




		sf::Sprite sprite;
		sprite.setTexture(m_deviceContext->m_resourceManager->getTexture("REAPER_IDLE_RIGHT"));
		sprite.setPosition(0.0f, 0.0f);
		sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));

		auto entity = std::make_unique<Player>(m_deviceContext);
		entity->setSprite(sprite);
		entity->setPosition(Vec2(0.0f, 916.0f));
		entity->setVelocity(Vec2(100.0f, 0.0f));

		entity->createAnimationList("Reaper.json");
		entity->setAnimation("IDLE_RIGHT");

		m_Player = entity.get();

		m_Entities.push_back(std::move(entity));*/

		m_deviceContext->m_resourceManager->playMusic("PLAYING_AUDIO");

		//m_tileMap = TileMap("TEST_SS", 100, 100, 20, 11, m_deviceContext);

		//m_tileMap.createTileMap("Test.json");

		//m_Physics->registerEntity(m_Player);
		//m_Physics->registerTileMap(&m_tileMap);

		/*m_View = m_renderWindow->getDefaultView();

		m_renderWindow->setView(m_View);*/

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
		for (const auto& entity : m_currentLevel->getEntities())
		{
			m_Physics->registerEntity(entity.get());
		}


		// Register Tilemap (for Collision Detection)

		m_Physics->registerTileMap(m_currentLevel->getTileMap().get());
		

	}









}