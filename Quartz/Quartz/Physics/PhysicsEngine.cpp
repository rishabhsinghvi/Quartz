#include "PhysicsEngine.h"

namespace Quartz
{
	void PhysicsEngine::init()
	{
		// NOTHING FOR NOW
	}

	void PhysicsEngine::update(float dt)
	{
		// Add gravitational force to all entities

		for (auto x : m_Entities)
		{
			x->addAcceleration(QUARTZ_GRAVITY);
		}




	}

	void PhysicsEngine::handleApplicationEvent(AppEvent& event)
	{
		if (event.eventType == EventType::PhysicsStartEvent)
			m_Running = true;
		else if (event.eventType == EventType::PhysicsStopEvent)
			m_Running = false;
	}

	void PhysicsEngine::clearEngine()
	{
		m_Entities.clear();
		m_tileMap = nullptr;
	}

	void PhysicsEngine::registerEntity(MoveableEntity* entity)
	{
		m_Entities.push_back(entity);
	}

	void PhysicsEngine::registerTileMap(TileMap* tileMap)
	{
		m_tileMap = tileMap;
	}
	void PhysicsEngine::detectCollisions()
	{
	}
}