#include "StateManager.h"

#include<iostream>

namespace Quartz
{
	void StateManager::init(DeviceContext* dc)
	{
		auto mainMenuState = std::make_unique<MainMenuState>();

		m_GameStates["MainMenu"] = std::move(mainMenuState);

		m_DeviceContext = dc;
	}

	void StateManager::loadState(const std::string& state)
	{
		auto s = m_GameStates.find(state);

		if (s == m_GameStates.end())
		{
			std::cout << "Invalid state...\n";
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