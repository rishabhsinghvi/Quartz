#ifndef QUARTZ_PLAYER_ENTITY_H
#define QUARTZ_PLAYER_ENTITY_H

#include "MoveableEntity.h"
#include "DeviceContext.h"

namespace Quartz
{
	class PlayerEntity : public MoveableEntity
	{
	public:
		enum class ActionState
		{
			None,
			Moving, Running, Slashing, Jumping, Falling, 
		};
	protected:
		// Variables to keep track of action
		ActionState m_State = ActionState::None;
	public:
		PlayerEntity(DeviceContext* dc);

		virtual void setSprite(const sf::Sprite& sprite) override;

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
	};
}

#endif