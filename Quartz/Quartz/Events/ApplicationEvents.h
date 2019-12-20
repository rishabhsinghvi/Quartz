#ifndef QUARTZ_APPLICATION_EVENTS_H
#define QUARTZ_APPLICATION_EVENTS_H

// Application Events are different from SFML generated events. While SFML generated events deal with mostly input, 
// Application Events deal with systems.
#include<string>
#include<variant>

namespace Quartz
{
	enum class EventType
	{
		None,
		StateChangeEvent,
		AppCloseEvent,
		PhysicsStartEvent,
		PhysicsStopEvent
	};

	struct AppEvent;
	class AppEventQueue;

	class Observable
	{
	public:
		
		virtual ~Observable() = default;

		virtual void handleApplicationEvent(AppEvent& event) = 0;
	};

	struct StateChangeEvent
	{
		std::string m_newState;

		StateChangeEvent() = default;

		StateChangeEvent(const std::string& newState) : m_newState(newState) {}

		StateChangeEvent(const StateChangeEvent& e) = default;

		~StateChangeEvent() = default;
	};

	struct AppCloseEvent
	{
		// NOTHING
	};


	struct AppEvent
	{
		EventType eventType = EventType::None;
		std::variant<StateChangeEvent, AppCloseEvent> m_Info;

		AppEvent() = default;

		AppEvent(const AppEvent& e) = default;

		~AppEvent() = default;

		
	};
}


#endif