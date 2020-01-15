#include "Application.h"
#include "Logger/Logger.h"

#include<string>


namespace Quartz
{
	
	static const std::string getWorkingDirectory()
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
	extern const std::string ENTITY_DIRECTORY = DIRECTORY + "Quartz/Resources/Entities/";
	extern const std::string ANIMATION_DIRECTORY = DIRECTORY + "Quartz/Resources/Animation/";
	extern const std::string TILEMAP_DIRECTORY = DIRECTORY + "Quartz/Resources/TileMap/";

	extern const unsigned int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width;
	extern const unsigned int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height;


	void Application::init()
	{
		m_Timer = std::make_unique<Timer>();
		
		// Create and intialize all subsystems
		
		m_Window = std::make_unique<Window>();
		m_resourceManager = std::make_unique<ResourceManager>();
		m_appEventQueue = std::make_unique<AppEventQueue>();
		m_inputHandler = std::make_unique<InputHandler>();
		m_stateManager = std::make_unique<StateManager>();

		m_deviceContext = std::make_unique<DeviceContext>();

		// Register necessary systems with the DeviceContext

		m_deviceContext->registerApplication(this);
		m_deviceContext->registerWindow(m_Window.get());
		m_deviceContext->registerResourceManager(m_resourceManager.get());
		m_deviceContext->registerEventQueue(m_appEventQueue.get());
		m_deviceContext->registerInputHandler(m_inputHandler.get());

		// Initialize all systems

		m_Window->init();
		m_resourceManager->init();
		
		m_stateManager->init(m_deviceContext.get());
		m_inputHandler->init(m_deviceContext.get());

		// Create event table
		m_appEventQueue->registerObservable(EventType::StateChangeEvent, this);
		m_appEventQueue->registerObservable(EventType::AppCloseEvent, this);
		

		// Load initial state
		m_stateManager->loadState("MainMenu");
	}							

	void Application::run()
	{

		/*float curDt = 0.0f;
		int frames = 0;*/

		m_Timer->reset();
		while (m_isRunning)
		{
			auto dt = m_Timer->getDeltaT();

		/*	frames++;
			curDt += dt;

			if (curDt >= 1.0f)
			{
				LOG_INFO("{0}", frames);
				curDt = 0.0f;
				frames = 0;
			}*/

			auto state = m_stateManager->getCurrentState();

			// Handle SFML events
			auto events = m_Window->getPolledEvents();

			for (auto& x : events)
			{
				state->handleInput(x);
			}

			// Handle Application events
			m_appEventQueue->dispatchEvents();

		
			m_Window->clear();

			state->update(dt);
			state->render();

			m_Window->update();
		}
		
	}
	void Application::handleApplicationEvent(AppEvent& event)
	{
		switch (event.eventType)
		{
		case EventType::StateChangeEvent:
		{
			m_stateManager->loadState(std::get<StateChangeEvent>(event.m_Info).m_newState);
			break;
		}
		case EventType::AppCloseEvent:
		{
			m_isRunning = false;
			break;
		}
		}
	}
}