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
		std::unique_ptr<sf::Cursor> m_Cursor;
	public:

		void init();

		void clear() const;

		void update() const;

		std::vector<sf::Event> getPolledEvents() const;

		sf::RenderWindow* getRenderWindow() const;
	};
}

#endif