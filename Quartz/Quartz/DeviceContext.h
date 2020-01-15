#ifndef QUARTZ_DEVICE_CONTEXT_H
#define QUARTZ_DEVICE_CONTEXT_H


namespace Quartz
{
	class ResourceManager;
	class Window;
	class Application;
	class AppEventQueue;
	class InputHandler;
	/*
	**  DeviceContext is simply a struct containing references to all the common subsystems.
	**  
	*/

	struct DeviceContext
	{
		ResourceManager* m_resourceManager;
		Window* m_Window;
		Application* m_Application;
		AppEventQueue* m_appEventQueue;
		InputHandler* m_inputHandler;

		DeviceContext() = default;

		void registerResourceManager(ResourceManager* rm)
		{
			m_resourceManager = rm;
		}

		void registerWindow(Window* w)
		{
			m_Window = w;
		}

		void registerApplication(Application* app)
		{
			m_Application = app;
		}

		void registerEventQueue(AppEventQueue* aeq)
		{
			m_appEventQueue = aeq;
		}

		void registerInputHandler(InputHandler* ih)
		{
			m_inputHandler = ih;
		}
	};
}

#endif