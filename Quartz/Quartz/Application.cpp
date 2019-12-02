#include "Application.h"

#include "MainMenuState.h"



#include "SFML/Audio.hpp"

#include<string>

namespace Quartz
{
	const std::string getWorkingDirectory()
	{
		auto fullPath = std::filesystem::current_path().string();
#ifdef USER_OS_WINDOWS
		auto pos = fullPath.find_last_of('\\');
#endif
		return fullPath.substr(0, pos + 1);
	}

	extern const std::string DIRECTORY = getWorkingDirectory();
	extern const std::string TEXTURE_DIRECTORY = DIRECTORY + "Quartz/Resources/Textures/";
	extern const std::string AUDIO_DIRECTORY = DIRECTORY + "Quartz/Resources/Audio/";
	extern const std::string CONFIG_DIRECTORY = DIRECTORY + "Quartz/Resources/Configs/";
	extern const std::string FONT_DIRECTORY = DIRECTORY + "Quartz/Resources/Fonts/";

	extern const unsigned int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width;
	extern const unsigned int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height;

	void Application::setRunningState(bool val)
	{
		m_isRunning = val;
	}

	void Application::init()
	{
		m_Window = std::make_unique<Window>();
		m_resourceManager = std::make_unique<ResourceManager>();



		m_Window->init();
		m_resourceManager->init();

		
		// Create device context
		m_deviceContext = std::make_unique<DeviceContext>(m_resourceManager.get(), m_Window.get(), this);

		// TODO: Set device context

	}							

	void Application::run()
	{
		auto state = std::make_unique<MainMenuState>();
		state->init(m_deviceContext.get());
		while (m_isRunning)
		{
			m_Window->clear();

			state->render();

			m_Window->pollEvents();
			m_Window->update();
		}
		
	}
}