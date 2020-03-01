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
#include<cstdint>

namespace Quartz
{
	namespace Flags
	{
		constexpr uint8_t X_DIR = 1 << 0;
		constexpr uint8_t Y_DIR = 1 << 1;
	}

	class PhysicsEngine: public Observable
	{
	private:
		struct CollisionInfo
		{
			Entity* m_First; 
			Entity* m_Second;
			uint8_t m_CollisionFlags = 0;

			CollisionInfo(Entity* a, Entity* b):
				m_First(a), m_Second(b)
			{
				// NOTHING
			}

			bool operator==(const CollisionInfo& other) const
			{
				return (m_First == other.m_First && m_Second == other.m_Second) 
					|| (m_First == other.m_Second && m_Second == other.m_First);
			}

			void addFlag(uint8_t flag)
			{
				m_CollisionFlags |= flag;
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
		//std::unordered_set<CollisionInfo, CollisionInfoHasher> m_CollisionSet;
	

	public:

		void init(); 

		void update(float dt);

		virtual void handleApplicationEvent(AppEvent& event) override;

		void clearEngine();

		void registerEntityList(const std::vector<std::unique_ptr<Entity>>& entityList);

		void registerEntity(Entity* entity);

		void registerTileMap(TileMap* tileMap);

	private:

		std::unordered_set<PhysicsEngine::CollisionInfo, PhysicsEngine::CollisionInfoHasher> detectCollisions();

		void resolveCollisions(const std::unordered_set<PhysicsEngine::CollisionInfo, PhysicsEngine::CollisionInfoHasher>&);

		std::optional<CollisionInfo> checkBoundingBoxCollision(Entity* a, Entity* b);

	};
}

#endif