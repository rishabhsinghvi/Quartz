#include "PhysicsEngine.h"
#include "Logger/Logger.h"

#include "SFML/Graphics.hpp"

#include<iostream>


namespace Quartz
{
	void PhysicsEngine::init()
	{
		// NOTHING FOR NOW
	}

	void PhysicsEngine::update(float dt)
	{
		// Add gravitational force to all entities

		// for Debugging


		/*for (auto x : m_Entities)
		{
			x->addAcceleration(QUARTZ_GRAVITY);

			int _x = x->getPosition().x / m_tileMap->getTileWidth();
			int _y = x->getPosition().y / m_tileMap->getTileHeight();

			static bool display = true;
			if (display)
			{
				LOG_INFO("{0}, {1}, {2}", _x, _y, m_tileMap->isCollidable(_x, _y));
				display = false;
			}
		}*/

		detectCollisions();


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

	void PhysicsEngine::registerEntityList(const std::vector<std::unique_ptr<Entity>>& entityList)
	{
		for (const auto& entity : entityList)
		{
			m_Entities.push_back(entity.get());
		}
	}

	void PhysicsEngine::registerEntity(Entity* entity)
	{
		m_Entities.push_back(entity);
	}

	void PhysicsEngine::registerTileMap(TileMap* tileMap)
	{
		m_tileMap = tileMap;
	}

	void PhysicsEngine::detectCollisions()
	{
		for (auto a : m_Entities)
		{
			for (auto b : m_Entities)
			{
				if (a == b)
					continue;

				checkBoundingBoxCollision(a, b);
			}
		}
	}

	std::optional<PhysicsEngine::CollisionInfo> PhysicsEngine::checkBoundingBoxCollision(Entity* a, Entity* b)
	{
		const auto& aBoundingBox = a->getBoundingBoxData();
		const auto& bBoundingBox = b->getBoundingBoxData();

		if(aBoundingBox.m_BoundingBox.intersects(bBoundingBox.m_BoundingBox))
		{
			LOG_INFO("Collision!");
			return std::make_optional<PhysicsEngine::CollisionInfo>(a, b);
		}

		return {};
	}

}