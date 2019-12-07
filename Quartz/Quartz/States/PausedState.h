#ifndef QUARTZ_PAUSED_STATE_H
#define QUARTZ_PAUSED_STATE_H


#include "GameState.h"
#include "UIElement.h"


namespace Quartz
{
	class PausedState : public GameState
	{
	private:
		DeviceContext* m_deviceContext = nullptr;
		sf::RenderWindow* m_renderWindow = nullptr;
		bool m_Initialized = false;
		std::vector<std::unique_ptr<UIElement>> m_UIEntities;

	public:

		virtual void init(DeviceContext* dc) override;

		virtual void destroy() override;

		virtual void paused() override;

		virtual void resumed() override;

		virtual void render() override;

		virtual void update(float dt) override;

		virtual void handleInput(sf::Event& event) override;

		virtual bool isInitialized() const override;

	};
}

#endif