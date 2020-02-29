#ifndef QUARTZ_PLAYER_ENTITY_H
#define QUARTZ_PLAYER_ENTITY_H

#include "MoveableEntity.h"
#include "DeviceContext.h"

#include<vector>
#include<functional>

namespace Quartz
{
	class Player : public MoveableEntity
	{
	public:
		enum ActionState
		{
			Idle,
			Moving, Running, Slashing, Jumping, Falling,
			RunningSlashing, MovingSlashing
		};
	protected:
		// Variables to keep track of action
		ActionState m_State = Idle;

	public:
		Player(DeviceContext* dc);

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

		virtual void setBoundingBoxDimensions(unsigned int w, unsigned int h);

		float getPositionX() const;

		float getPositionY() const;

	private:

		virtual void setToAnimation(const std::string& textureName, const std::string& animationName);

	};


}

#endif