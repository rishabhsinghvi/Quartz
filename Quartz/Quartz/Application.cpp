#include "Application.h"


#include "SFML/Audio.hpp"

#include<string>

namespace Quartz
{
	void Application::init()
	{
		m_Window = std::make_unique<Window>();
		m_Renderer = std::make_unique<Renderer>(); 
		m_resourceManager = std::make_unique<ResourceManager>();



		m_Window->init();
		
		m_Renderer->init(m_Window->getRenderWindow());
		
		m_resourceManager->init();

		m_resourceManager->loadTexturesFromFile("../Quartz/Resources/Configs/Textures.json");
		m_resourceManager->loadSpritesFromFile("../Quartz/Resources/Configs/Sprites.json");


	}							

	void Application::run()
	{
		while (m_isRunning)
		{
			m_Window->clear();

			m_Window->pollEvents();
			m_Window->update();
		}
		
	}
}