#ifndef QUARTZ_GAME_STATE_H
#define QUARTZ_GAME_STATE_H

#include "SFML/Graphics.hpp"

namespace Quartz
{

	struct DeviceContext;

	class GameState
	{
	public:

		virtual void init(DeviceContext* dc) = 0;

		virtual void destroy() = 0;

		virtual void paused() = 0;

		virtual void resumed() = 0;

		virtual void render() = 0;

		virtual void handleInput(sf::Event& event) = 0;

		virtual bool isInitialized() const = 0;
	};
}


#endif