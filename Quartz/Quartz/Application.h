#ifndef QUARTZ_APPLICATION_H
#define QUARTZ_APPLICATION_H

#include "Window.h"
#include "ResourceManager.h"
#include "DeviceContext.h"



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
		std::unique_ptr<ResourceManager> m_resourceManager;
		std::unique_ptr<DeviceContext> m_deviceContext;

		bool m_isRunning = true;

	public:
		void setRunningState(bool val);

		void init();

		void run();
	};
}

#endif