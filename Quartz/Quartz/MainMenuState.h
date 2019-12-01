#ifndef QUARTZ_MAIN_MENU_STATE_H
#define QUARTZ_MAIN_MENU_STATE_H

#include "GameState.h"
#include "DeviceContext.h"

namespace Quartz
{
	class MainMenuState : public GameState
	{
	private:
		DeviceContext* m_deviceContext = nullptr;
		bool m_Initialized = false;

	public:


		virtual void init(DeviceContext* dc) override;

		virtual void destroy() override;

		virtual void paused() override;

		virtual void resumed() override;

		virtual void render() override;

		virtual void handleInput(sf::Event& event) override;
	};
}

#endif