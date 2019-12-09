#include "StateManager.h"
#include "States/PlayingState.h"
#include "States/PausedState.h"
#include "Logger/Logger.h"

#include<iostream>

namespace Quartz
{
	void StateManager::init(DeviceContext* dc)
	{
		auto mainMenuState = std::make_unique<MainMenuState>();
		auto playingState = std::make_unique<PlayingState>();
		auto pausedState = std::make_unique<PausedState>();

		m_GameStates["MainMenu"] = std::move(mainMenuState);
		m_GameStates["Playing"] = std::move(playingState);
		m_GameStates["Paused"] = std::move(pausedState);

		m_DeviceContext = dc;
	}

	void StateManager::loadState(const std::string& state)
	{
		auto s = m_GameStates.find(state);

		if (s == m_GameStates.end())
		{
			LOG_ERROR("StateManager: Invalid state {0}", state);
			__debugbreak();
		}

		auto newState = s->second.get();

		if (!newState->isInitialized())
			newState->init(m_DeviceContext);


		m_currentState = newState;

		
	}

	GameState* StateManager::getCurrentState()
	{
		return m_currentState;
	}


}