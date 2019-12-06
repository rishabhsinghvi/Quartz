#ifndef QUARTZ_APP_EVENT_QUEUE
#define QUARTZ_APP_EVENT_QUEUE

#include "ApplicationEvents.h"

#include<unordered_map>
#include<vector>

namespace Quartz
{
	class AppEventQueue
	{
	private:
		std::vector<AppEvent> m_eventList;
		std::vector<AppEvent> m_nextFrameEventList;
		std::unordered_map<EventType, std::vector<Observable*>> m_Observables;

	public:

		void registerObservable(EventType eventType, Observable* observable);

		void addEventToQueue(AppEvent& event);

		void dispatchEvents();

	};
}

#endif