#ifndef QUARTZ_STATE_MANAGER_H
#define QUARTZ_STATE_MANAGER_H

#include "States/GameState.h"
#include "States/MainMenuState.h"
#include "DeviceContext.h"

#include<unordered_map>
#include<memory>
#include<string>

namespace Quartz
{
	class StateManager
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<GameState>> m_GameStates;
		GameState* m_currentState = nullptr;
		DeviceContext* m_DeviceContext = nullptr;
	public:

		void init(DeviceContext* dc);

		void loadState(const std::string& state);

		GameState* getCurrentState();
	};
}

#endif