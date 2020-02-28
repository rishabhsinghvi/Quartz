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

namespace Quartz
{
	class PhysicsEngine: public Observable
	{
	private:
		std::vector<Entity*> m_Entities;
		TileMap* m_tileMap = nullptr;
		bool m_Running = true;

	public:

		void init(); 

		void update(float dt);

		virtual void handleApplicationEvent(AppEvent& event) override;

		void clearEngine();

		void registerEntityList(const std::vector<std::unique_ptr<Entity>>& entityList);

		void registerEntity(Entity* entity);

		void registerTileMap(TileMap* tileMap);

		void detectCollisions();
		
	};
}

#endif