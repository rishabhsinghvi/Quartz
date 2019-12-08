#ifndef QUARTZ_PLAYER_ENTITY_H
#define QUARTZ_PLAYER_ENTITY_H

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
	private:
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

	public:


		MoveableEntity(DeviceContext* w);

		void setSprite(const sf::Sprite& sprite); 

		virtual void update(float dt) override;

		virtual void render() const override;
		
		virtual sf::Sprite* getSprite() override;

		void setPosition(const Vec2& pos);

		void setVelocity(const Vec2& vel);

		void setAcceleration(const Vec2& vel);

		void setDirection(Direction dir);

		Direction getDirection() const;

		void createAnimationList(const std::string& fileName);
		
		void setAnimation(const std::string& name);

		void setSpriteDimensions(unsigned int w, unsigned int h);

	};
}

#endif