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


		auto collisionSet = detectCollisions();
		resolveCollisions(collisionSet);

		for (auto x : m_Entities)
		{
			x->setPosition(x->getPosition() + x->getVelocity() * dt);
			x->setVelocity(Vec2(0.0f, 0.0f));
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

	/*
	*  Considering the relative few amount of entities in a level, a simple
	* O(n^2) search through all entities would suffice. 
	*/
	std::unordered_set<PhysicsEngine::CollisionInfo, PhysicsEngine::CollisionInfoHasher> PhysicsEngine::detectCollisions()
	{
		std::unordered_set<CollisionInfo, CollisionInfoHasher> collisionSet;
		for (auto a : m_Entities)
		{
			for (auto b : m_Entities)
			{
				if (a == b)
					continue;

				auto collisionInfo = checkBoundingBoxCollision(a, b);
				if (collisionInfo.has_value())
				{
					collisionSet.insert(std::move(collisionInfo.value()));
				}
			}
		}
		return collisionSet;
	}

	// TERRIBLE. Change this.
	void PhysicsEngine::resolveCollisions(const std::unordered_set<PhysicsEngine::CollisionInfo, PhysicsEngine::CollisionInfoHasher>& collisionSet)
	{
		for (const auto& col : collisionSet)
		{
			auto a = col.m_First;
			auto b = col.m_Second;

			// A very basic collision resolution
			
			if (col.m_CollisionFlags & Flags::X_DIR > 0)
			{
				a->setVelocityX(0.0f);
				b->setVelocityX(0.0f);
			}

			if (col.m_CollisionFlags & Flags::Y_DIR > 0)
			{
				a->setVelocityY(0.0f);
				b->setVelocityY(0.0f);
			}

			//LOG_INFO("Hello!\n");
		}
	}

	std::optional<PhysicsEngine::CollisionInfo> PhysicsEngine::checkBoundingBoxCollision(Entity* a, Entity* b)
	{
		const auto& aBoundingBox = a->getBoundingBoxData();
		const auto& bBoundingBox = b->getBoundingBoxData();

		if(aBoundingBox.m_BoundingBox.intersects(bBoundingBox.m_BoundingBox))
		{
			CollisionInfo colInfo(a, b);
			
			// Check whether collision in X direction
			if ((aBoundingBox.x + aBoundingBox.width > bBoundingBox.x) && (aBoundingBox.x < bBoundingBox.x + bBoundingBox.width))
			{
				LOG_INFO("X DIR");
				colInfo.addFlag(Flags::X_DIR);
			}

			// Checks whether collision in Y direction
			if ((aBoundingBox.y < bBoundingBox.y + bBoundingBox.height) && (aBoundingBox.y + aBoundingBox.height > bBoundingBox.height))
			{
				LOG_INFO("Y_DIR");
				colInfo.addFlag(Flags::Y_DIR);
			}

			return colInfo;
		}

		return {};
	}

}