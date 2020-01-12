#include "PlayerEntity.h"
#include "ResourceManager.h"
#include "Logger/Logger.h"

#define KEY_PRESSED(x) sf::Keyboard::isKeyPressed(sf::Keyboard::##x)
#define MOUSE_PRESSED(x) sf::Mouse::isButtonPressed(sf::Mouse::##x)

constexpr float RUNNING_SPEEDUP = 2.0f;


namespace Quartz
{
	PlayerEntity::PlayerEntity(DeviceContext* dc): MoveableEntity(dc)
	{
		buildMovementMatrix();
	}
	void PlayerEntity::setSprite(const sf::Sprite& sprite)
	{
		MoveableEntity::setSprite(sprite);
	}

	void PlayerEntity::update(float dt)
	{
		auto keycode = Input::getUserInput();

		// Run
		//if (KEY_PRESSED(D) && KEY_PRESSED(LShift) && MOUSE_PRESSED(Left))
		//{
		//	if (m_State != PlayerEntity::ActionState::RunningSlashing)
		//	{
		//		m_State = PlayerEntity::ActionState::RunningSlashing;

		//		setToAnimation("REAPER_RUNNING_SLASHING_RIGHT", "RUNNING_SLASHING_RIGHT");
		//	}
		//	else
		//	{
		//		if (m_Animation->isAnimationDone())
		//		{
		//			m_State = PlayerEntity::ActionState::Running;
		//			setToAnimation("REAPER_RUNNING_RIGHT", "RUNNING_RIGHT");
		//		}
		//		else
		//		{
		//			m_Pos += (m_Vel * RUNNING_SPEEDUP) * dt;
		//			m_Sprite.setPosition(m_Pos.x, m_Pos.y);
		//			m_Animation->update(dt);
		//		}
		//	}
		//}
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		//{
		//	if (m_Direction == MoveableEntity::Direction::Left || m_State != PlayerEntity::ActionState::Running)
		//	{
		//		m_State = PlayerEntity::ActionState::Running;
		//		m_Direction = MoveableEntity::Direction::Right;

		//		setToAnimation("REAPER_RUNNING_RIGHT", "RUNNING_RIGHT");
		//	}
		//	else
		//	{
		//		m_Pos += (m_Vel * RUNNING_SPEEDUP) * dt;
		//		m_Sprite.setPosition(m_Pos.x, m_Pos.y);
		//		m_Animation->update(dt);
		//	}
		//}

		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		//{
		//	if (m_Direction == MoveableEntity::Direction::Right || m_State != PlayerEntity::ActionState::Running)
		//	{
		//		m_State = PlayerEntity::ActionState::Running;
		//		m_Direction = MoveableEntity::Direction::Left;

		//		setToAnimation("REAPER_RUNNING_LEFT", "RUNNING_LEFT");
		//	}
		//	else
		//	{
		//		m_Pos -= (m_Vel * RUNNING_SPEEDUP) * dt;
		//		m_Sprite.setPosition(m_Pos.x, m_Pos.y);
		//		m_Animation->update(dt);
		//	}
		//}

		//// Walk
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		//{

		//	 if (m_Direction == MoveableEntity::Direction::Left || m_State != PlayerEntity::ActionState::Moving)
		//	{
		//		m_State = PlayerEntity::ActionState::Moving;
		//		m_Direction = MoveableEntity::Direction::Right;

		//		setToAnimation("REAPER_WALKING_RIGHT", "WALKING_RIGHT");
		//	}
		//	else if (m_Direction == MoveableEntity::Direction::Right)
		//	{
		//		m_Pos += m_Vel * dt;
		//		m_Sprite.setPosition(m_Pos.x, m_Pos.y);
		//		m_Animation->update(dt);
		//	}
		//}
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		//{
		//	if (m_Direction == MoveableEntity::Direction::Right || m_State != PlayerEntity::ActionState::Moving)
		//	{
		//		m_State = PlayerEntity::ActionState::Moving;
		//		m_Direction = MoveableEntity::Direction::Left;

		//		setToAnimation("REAPER_WALKING_LEFT", "WALKING_LEFT");
		//	}
		//	else if (m_Direction == MoveableEntity::Direction::Left)
		//	{
		//		m_Pos -= (m_Vel * dt);
		//		m_Sprite.setPosition(m_Pos.x, m_Pos.y);
		//		m_Animation->update(dt);
		//	}
		//	
		//}

		//else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_State != PlayerEntity::ActionState::Slashing && m_Direction == MoveableEntity::Direction::Right)
		//{
		//	m_State = PlayerEntity::ActionState::Slashing;

		//	setToAnimation("REAPER_SLASHING_RIGHT", "SLASHING_RIGHT");
		//}

		//else if (m_State == PlayerEntity::ActionState::Slashing)
		//{
		//	if (m_Animation->isAnimationDone())
		//	{
		//		m_State = PlayerEntity::ActionState::Idle;

		//		setToAnimation("REAPER_IDLE_RIGHT", "IDLE_RIGHT");
		//	}
		//	else
		//	{
		//		m_Animation->update(dt);
		//	}
		//}


		////
		//else if (m_Direction == MoveableEntity::Direction::Right)
		//{
		//	if (m_State != PlayerEntity::ActionState::Idle)
		//	{
		//		m_State = PlayerEntity::ActionState::Idle;
		//		
		//		setToAnimation("REAPER_IDLE_RIGHT", "IDLE_RIGHT");
		//	}
		//	else
		//	{
		//		m_Animation->update(dt);
		//	}
		//
		//}
		//else if (m_Direction == MoveableEntity::Direction::Left)
		//{
		//	if (m_State != PlayerEntity::ActionState::Idle)
		//	{
		//		m_State = PlayerEntity::ActionState::Idle;
		//		
		//		setToAnimation("REAPER_IDLE_LEFT", "IDLE_LEFT");
		//	}
		//	else
		//	{
		//		m_Animation->update(dt);
		//	}
		//}
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

	float PlayerEntity::getPositionX() const
	{
		return m_Pos.x;
	}

	float PlayerEntity::getPositionY() const
	{
		return m_Pos.y;
	}



	void PlayerEntity::setToAnimation(const std::string& textureName, const std::string& animationName)
	{
		m_Sprite.setTexture(m_deviceContext->m_resourceManager->getTexture(textureName));
		m_Sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
		setAnimation(animationName);
		m_Animation->reset();
	}

	

}

namespace Quartz
{
	namespace Input
	{

		Keycode getUserInput()
		{
			if (KEY_PRESSED(D) && KEY_PRESSED(LShift))
			{
				return K_ShiftD;
			}
			else if (KEY_PRESSED(A) && KEY_PRESSED(LShift))
			{
				return K_ShiftA;
			}
			else if (KEY_PRESSED(D))
			{
				return K_D;
			}
			else if (KEY_PRESSED(A))
			{
				return K_A;
			}
			else if (KEY_PRESSED(Space))
			{
				return K_Space;
			}
			else if(MOUSE_PRESSED(Left))
			{
				return K_Mouse1;
			}
			else
			{
				return K_None;
			}

		}
	}
}
