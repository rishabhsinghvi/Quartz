#include "AppEventQueue.h"

namespace Quartz
{
	void AppEventQueue::registerObservable(EventType eventType, Observable* observable)
	{
		m_Observables[eventType].push_back(observable);
		//observable->setAppEventQueue(this);
	}

	void AppEventQueue::addEventToQueue(AppEvent& event)
	{
		m_nextFrameEventList.push_back(std::move(event));
	}


	void AppEventQueue::dispatchEvents()
	{
		std::swap(m_eventList, m_nextFrameEventList);

		if (m_eventList.size() == 0)
			return;

		for (auto& event : m_eventList)
		{
			auto type = event.eventType;
			auto observables = m_Observables.find(type);

			if (observables == m_Observables.end())
				continue;

			for (auto system : observables->second)
			{
				system->handleApplicationEvent(event);
			}

		}

		m_eventList.clear();

	}


}