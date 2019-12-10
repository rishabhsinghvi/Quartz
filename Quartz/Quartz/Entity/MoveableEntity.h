#ifndef QUARTZ_MOVEABLE_ENTITY_H
#define QUARTZ_MOVEABLE_ENTITY_H

#include "Entity.h"
#include "DeviceContext.h"
#include "Math/Vec2.h"
#include "Animation/Animation.h"

#include <unordered_map>
#include <string>
#include <memory>

namespace Quartz
{
	class MoveableEntity : public Entity
	{
	public:
		enum class Direction
		{
			Left, Right
		};
	protected:
		DeviceContext* m_deviceContext;
		Animation* m_Animation = nullptr;
		sf::Sprite m_Sprite;
		Vec2 m_Pos;
		Vec2 m_Vel;
		Vec2 m_Acc;
		unsigned int m_SpriteWidth;
		unsigned int m_SpriteHeight;
		std::unordered_map<std::string, std::unique_ptr<Animation>> m_AnimationList;
		Direction m_Direction = Direction::Right;
		Entity::EntityType m_entityType = Entity::EntityType::Moveable;

	public:


		MoveableEntity(DeviceContext* w);

		virtual void setSprite(const sf::Sprite& sprite); 

		virtual void update(float dt) override;

		virtual void render() const override;
		
		virtual sf::Sprite* getSprite() override;

		virtual void setPosition(const Vec2& pos);

		virtual	void setVelocity(const Vec2& vel);

		virtual void setAcceleration(const Vec2& vel);

		virtual void setDirection(Direction dir);

		virtual Direction getDirection() const;

		virtual void createAnimationList(const std::string& fileName);
		
		virtual void setAnimation(const std::string& name);

		virtual void setSpriteDimensions(unsigned int w, unsigned int h);

		Entity::EntityType getEntityType() const;

	};
}

#endif