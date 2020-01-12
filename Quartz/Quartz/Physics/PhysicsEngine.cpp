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

	void PhysicsEngine::clearEngine()
	{
		m_Entities.clear();
		m_tileMap = nullptr;
	}

	void PhysicsEngine::registerEntity(Entity* entity)
	{
		m_Entities.push_back(entity);
	}

	void PhysicsEngine::registerTileMap(TileMap* tileMap)
	{
		m_tileMap = tileMap;
	}
}