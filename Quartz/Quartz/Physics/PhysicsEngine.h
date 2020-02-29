#ifndef QUARTZ_PHYSICS_ENGINE_H
#define QUARTZ_PHYSICS_ENGINE_H

#include "Math/Vec2.h"
#include "Constants.h"
#include "Entity/Entity.h"
#include "Entity/MoveableEntity.h"
#include "Events/AppEventQueue.h"
#include "Events/ApplicationEvents.h"
#include "TileMap/TileMap.h"

#include <vector>
#include<unordered_set>
#include<optional>

namespace Quartz
{
	class PhysicsEngine: public Observable
	{
	private:
		struct CollisionInfo
		{
			Entity* m_First; 
			Entity* m_Second;

			CollisionInfo(Entity* a, Entity* b):
				m_First(a), m_Second(b)
			{
			
			}

			bool operator==(const CollisionInfo& other) const
			{
				return (m_First == other.m_First && m_Second == other.m_Second) 
					|| (m_First == other.m_Second && m_Second == other.m_First);
			}

		};

		struct CollisionInfoHasher
		{
			unsigned int operator()(const CollisionInfo& info) const noexcept
			{
				return std::hash<Entity*>{}(info.m_First) ^ (std::hash<Entity*>{}(info.m_Second) << 1);
			}
		};

		std::vector<Entity*> m_Entities;
		TileMap* m_tileMap = nullptr;
		bool m_Running = true;
		std::unordered_set<CollisionInfo, CollisionInfoHasher> m_CollisionSet;
	

	public:

		void init(); 

		void update(float dt);

		virtual void handleApplicationEvent(AppEvent& event) override;

		void clearEngine();

		void registerEntityList(const std::vector<std::unique_ptr<Entity>>& entityList);

		void registerEntity(Entity* entity);

		void registerTileMap(TileMap* tileMap);

	private:

		void detectCollisions();

		std::optional<CollisionInfo> checkBoundingBoxCollision(Entity* a, Entity* b);

	};
}

#endif