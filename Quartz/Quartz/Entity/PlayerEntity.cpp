#include "PlayerEntity.h"
#include "ResourceManager.h"
#include "Logger/Logger.h"

namespace Quartz
{
	PlayerEntity::PlayerEntity(DeviceContext* dc): MoveableEntity(dc)
	{

	}
	void PlayerEntity::setSprite(const sf::Sprite& sprite)
	{
		MoveableEntity::setSprite(sprite);
	}

	void PlayerEntity::update(float dt)
	{
		// FOR NOW
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{

			 if (m_Direction == MoveableEntity::Direction::Left || m_State != PlayerEntity::ActionState::Moving)
			{
				m_State = PlayerEntity::ActionState::Moving;
				m_Sprite.setTexture(m_deviceContext->m_resourceManager->getTexture("REAPER_WALKING_RIGHT"));
				m_Sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
				setAnimation("WALKING_RIGHT");
				m_Animation->reset();
				m_Direction = MoveableEntity::Direction::Right;
			}
			else if (m_Direction == MoveableEntity::Direction::Right)
			{
				m_Pos += m_Vel * dt;
				m_Sprite.setPosition(m_Pos.x, m_Pos.y);
				m_Animation->update(dt);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (m_Direction == MoveableEntity::Direction::Right || m_State != PlayerEntity::ActionState::Moving)
			{
				m_State = PlayerEntity::ActionState::Moving;
				m_Sprite.setTexture(m_deviceContext->m_resourceManager->getTexture("REAPER_WALKING_LEFT"));
				m_Sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
				setAnimation("WALKING_LEFT");
				m_Animation->reset();
				m_Direction = MoveableEntity::Direction::Left;
			}
			else if (m_Direction == MoveableEntity::Direction::Left)
			{
				m_Pos -= (m_Vel * dt);
				m_Sprite.setPosition(m_Pos.x, m_Pos.y);
				m_Animation->update(dt);
			}
			
		}
	}

	void PlayerEntity::render() const
	{
		MoveableEntity::render();
	}

	sf::Sprite* PlayerEntity::getSprite()
	{
		return MoveableEntity::getSprite();
	}

	void PlayerEntity::setPosition(const Vec2& pos)
	{
		MoveableEntity::setPosition(pos);
	}

	void PlayerEntity::setVelocity(const Vec2& vel)
	{
		MoveableEntity::setVelocity(vel);
	}

	void PlayerEntity::setAcceleration(const Vec2& vel)
	{
		MoveableEntity::setAcceleration(vel);
	}

	void PlayerEntity::setDirection(Direction dir)
	{
		MoveableEntity::setDirection(dir);
	}

	MoveableEntity::Direction PlayerEntity::getDirection() const
	{
		return MoveableEntity::getDirection();
	}

	void PlayerEntity::createAnimationList(const std::string& fileName)
	{
		MoveableEntity::createAnimationList(fileName);
	}

	void PlayerEntity::setAnimation(const std::string& name)
	{
		MoveableEntity::setAnimation(name);
	}

	void PlayerEntity::setSpriteDimensions(unsigned int w, unsigned int h)
	{
		MoveableEntity::setSpriteDimensions(w, h);
	}


}