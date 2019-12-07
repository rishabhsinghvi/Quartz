#include "PlayingState.h"
#include "DeviceContext.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Animation/Animation.h"
#include "Animation/AnimatedSprite.h"
#include "Events/ApplicationEvents.h"
#include "Events/AppEventQueue.h"

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

		
		//

		m_deviceContext->m_resourceManager->loadTexture("REAPER_FALLING_SHEET", "C:\\Users\\rdpsi\\Downloads\\output-onlinepngtools.png");

		auto animation = std::make_unique<Animation>();
		animation->setTexture(m_deviceContext->m_resourceManager->getTexturePointer("REAPER_FALLING_SHEET"));

		animation->addFrame(sf::IntRect(0, 0, 100, 100));
		animation->addFrame(sf::IntRect(100, 0, 100, 100));
		animation->addFrame(sf::IntRect(0, 100, 100, 100));
		animation->addFrame(sf::IntRect(100, 100, 100, 100));
		animation->addFrame(sf::IntRect(0, 200, 100, 100));
		animation->addFrame(sf::IntRect(100, 200, 100, 100));

		AnimatedSprite sprite;
		sprite.setFrameTime(0.2f);
		sprite.setLooping(false);
		sprite.setPosition(0.0f, 0.0f);


		auto ptr = std::make_unique<PlayerEntity>(m_deviceContext);

		ptr->setSprite(sprite);
		ptr->pushAnimation("FALLING", std::move(animation));
		ptr->setAnimation("FALLING");
		ptr->startAnimation();

		


		//



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
		// NOTHING FOR NOW
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
				event.m_Info.emplace<StateChangeEvent>("MainMenu");

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