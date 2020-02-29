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

		virtual void setSprite(const sf::Sprite& sprite) override;

		virtual void update(float dt) override;

		virtual void render() const override;

		virtual sf::Sprite* getSprite() override;

		virtual const Vec2& getPosition() const;

		const Vec2& getVelocity() const;

		virtual void setPosition(const Vec2& pos);

		virtual	void setVelocity(const Vec2& vel);

		virtual void setAcceleration(const Vec2& vel);

		virtual void setDirection(Direction dir);

		virtual Direction getDirection() const;

		virtual void createAnimationList(const std::string& fileName);

		virtual void setAnimation(const std::string& name);

		virtual void setBoundingBoxDimensions(unsigned int w, unsigned int h);

		void addAcceleration(const Vec2& force);

		Entity::EntityType getEntityType() const;

	};
}

#endif