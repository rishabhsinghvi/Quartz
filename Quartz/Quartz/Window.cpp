#include "Window.h"

#include<iostream>


namespace Quartz
{
	void Window::init()
	{
		m_Window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getFullscreenModes()[0], "Quartz", sf::Style::Fullscreen);
		
	}

	void Window::clear() const
	{
		m_Window->clear(sf::Color::Black);
	}

	void Window::update() const
	{
		m_Window->display();
	}

	void Window::pollEvents() const
	{
		sf::Event event;
		while (m_Window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_Window->close();
			}
		}
	}

	/*
	This function is used to pass around the sf::RenderWindow object, as a common context to other classes
	*/
	sf::RenderWindow* Window::getRenderWindow() const
	{
		return m_Window.get();
	}

	
}