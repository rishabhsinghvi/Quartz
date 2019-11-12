#ifndef QUARTZ_WINDOW_H
#define QUARTZ_WINDOW_H

#include "SFML/Graphics.hpp"

#include<memory>
namespace Quartz
{
	class Window
	{
	private:
		std::unique_ptr<sf::RenderWindow> m_Window;	
	public:

		void init();

		void clear() const;

		void update() const;

		void pollEvents() const;

		sf::RenderWindow* getRenderWindow() const;
	};
}

#endif