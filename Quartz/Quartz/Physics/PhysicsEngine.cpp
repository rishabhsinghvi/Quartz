#include "PhysicsEngine.h"

namespace Quartz
{
	void PhysicsEngine::init()
	{
		// NOTHING FOR NOW
	}

	void PhysicsEngine::update(float dt)
	{

	}

	void PhysicsEngine::handleApplicationEvent(AppEvent& event)
	{
		if (event.eventType == EventType::PhysicsStartEvent)
			m_Running = true;
		else if (event.eventType == EventType::PhysicsStopEvent)
			m_Running = false;
	}
	void PhysicsEngine::clearEntities()
	{
		m_Entities.clear();
	}
}