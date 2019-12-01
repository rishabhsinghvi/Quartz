#ifndef QUARTZ_DEVICE_CONTEXT_H
#define QUARTZ_DEVICE_CONTEXT_H


namespace Quartz
{
	class ResourceManager;
	class Window;
	class Application;

	/*
	**  DeviceContext is simply a struct containing references to all the common subsystems.
	**  
	*/

	struct DeviceContext
	{
		ResourceManager* m_resourceManager;
		Window* m_Window;
		Application* m_Application;

		DeviceContext() = default;

		DeviceContext(ResourceManager* resourceManager, Window* window, Application* app) :
			m_resourceManager(resourceManager), m_Window(window), m_Application(app)
		{
			// EMPTY
		}
	};
}

#endif