#ifndef QUARTZ_APPLICATION_H
#define QUARTZ_APPLICATION_H

#include "Window.h"
#include "Renderer.h"
#include "ResourceManager.h"


#include<memory>

#include "SFML/Graphics.hpp"

namespace Quartz
{
	class Application
	{
	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<ResourceManager> m_resourceManager;

		bool m_isRunning = true;

	public:

		void init();

		void run();
	};
}

#endif