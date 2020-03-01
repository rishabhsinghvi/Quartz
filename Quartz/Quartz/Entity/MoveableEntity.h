#ifndef QUARTZ_MOVEABLE_ENTITY_H
#define QUARTZ_MOVEABLE_ENTITY_H

#include "Entity.h"
#include "DeviceContext.h"

#include <unordered_map>
#include <string>
#include <memory>

namespace Quartz
{
	class MoveableEntity : public Entity
	{
	public:
		enum Direction
		{
			Left, Right
		};
	protected:
		Vec2 m_Vel;
		Vec2 m_Acc;
		Direction m_Direction = Right;
		Entity::EntityType m_entityType = Entity::EntityType::Moveable;

	public:


		MoveableEntity(DeviceContext* w);


		virtual Vec2 getVelocity() const override;


		virtual	void setVelocity(const Vec2& vel);

		virtual void setAcceleration(const Vec2& vel);

		virtual void setDirection(Direction dir);

		virtual Direction getDirection() const;

		virtual void setVelocityX(float x) override;

		virtual void setVelocityY(float y) override;

		void addAcceleration(const Vec2& force);

		Entity::EntityType getEntityType() const;

	};
}

#endif