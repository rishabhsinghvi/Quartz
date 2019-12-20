#ifndef QUARTZ_PHYSICS_ENGINE_H
#define QUARTZ_PHYSICS_ENGINE_H

#include "Math/Vec2.h"
#include "Constants.h"
#include "Entity/Entity.h"
#include "Events/AppEventQueue.h"
#include "Events/ApplicationEvents.h"

#include <vector>

namespace Quartz
{
	class PhysicsEngine: public Observable
	{
	private:
		std::vector<Entity*> m_Entities;
		bool m_Running = true;

	public:

		void init(); 

		void update(float dt);

		virtual void handleApplicationEvent(AppEvent& event) override;

		void clearEntities();
		
	};
}

#endif