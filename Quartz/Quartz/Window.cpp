#include "Window.h"

#include<iostream>
#include<vector>

namespace Quartz
{
	void Window::init()
	{
		m_Window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getFullscreenModes()[0], "Quartz", sf::Style::Fullscreen);
		m_Cursor = std::make_unique<sf::Cursor>();
		
		if (m_Cursor->loadFromSystem(sf::Cursor::Hand))
			m_Window->setMouseCursor(*m_Cursor);
		//m_Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Quartz");
	}

	void Window::clear() const
	{
		m_Window->clear(sf::Color::Black);
	}

	void Window::update() const
	{
		m_Window->display();
	}

	std::vector<sf::Event> Window::getPolledEvents() const
	{
		std::vector<sf::Event> events;
		sf::Event event;
		while (m_Window->pollEvent(event))
		{
			events.push_back(event);
		}

		return events;

	}

	/*
	This function is used to pass around the sf::RenderWindow object, as a common context to other classes
	*/
	sf::RenderWindow* Window::getRenderWindow() const
	{
		return m_Window.get();
	}

	
}