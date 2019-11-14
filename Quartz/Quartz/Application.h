#ifndef QUARTZ_APPLICATION_H
#define QUARTZ_APPLICATION_H

#include "Window.h"
#include "Renderer.h"
#include "ResourceManager.h"


#include<memory>
#include<string>
#include<filesystem>

#include "SFML/Graphics.hpp"

#if defined(_WIN32) || defined(_WIN64)
	#define USER_OS_WINDOWS
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
	#define USER_OS_UNIX
#endif

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