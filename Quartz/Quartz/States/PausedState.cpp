#include "PausedState.h"
#include "Events/ApplicationEvents.h"
#include "Events/AppEventQueue.h"
#include "Window.h"
#include "UI/UIButton.h"

namespace Quartz
{
	void PausedState::init(DeviceContext* dc)
	{
		if (m_Initialized)
		{
			return;
		}

		m_deviceContext = dc;
		m_renderWindow = m_deviceContext->m_Window->getRenderWindow();

		auto resumeButton = std::make_unique<UIButton>(0.48f, 0.4f, 0.5f, 0.5f, "Resume");
		auto exitButton = std::make_unique<UIButton>(0.48f, 0.5f, 0.5f, 0.5f, "Exit");

		resumeButton->setCallback([](DeviceContext* dc)
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

		m_UIEntities.push_back(std::move(resumeButton));
		m_UIEntities.push_back(std::move(exitButton));

		m_Initialized = true;

	}


	void PausedState::destroy()
	{
		m_Initialized = false;
	}

	void PausedState::paused()
	{
		// NOTHING
	}

	void PausedState::resumed()
	{
		// NOTHING
	}

	void PausedState::render()
	{

		auto mousePos = sf::Mouse::getPosition(*m_renderWindow);

		for (auto& ui : m_UIEntities)
		{
			ui->onHover(mousePos.x, mousePos.y);
			m_renderWindow->draw(*ui);
		}
	}

	void PausedState::update(float dt)
	{
		// NOTHING 
	}

	void PausedState::handleInput(sf::Event& event)
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonReleased:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				auto mousePos = sf::Mouse::getPosition(*m_renderWindow);

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
		}
	}

	bool PausedState::isInitialized() const
	{
		return m_Initialized;
	}


}