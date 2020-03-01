#include "Player.h"
#include "ResourceManager.h"
#include "InputHandler.h"
#include "Logger/Logger.h"

#define KEY_PRESSED(x) sf::Keyboard::isKeyPressed(sf::Keyboard::##x)
#define MOUSE_PRESSED(x) sf::Mouse::isButtonPressed(sf::Mouse::##x)

constexpr float RUNNING_SPEEDUP = 2.0f;


namespace Quartz
{
	Player::Player(DeviceContext* dc): MoveableEntity(dc)
	{

	}

	void Player::setSprite(const sf::Sprite& sprite)
	{
		MoveableEntity::setSprite(sprite);
	}

	void Player::update(float dt)
	{

		auto input = m_deviceContext->m_inputHandler->getUserInput();

		switch (input)
		{
		case Action::A_RunRight:
		{
			if (m_Direction == MoveableEntity::Direction::Left || m_State != Player::ActionState::Running)
			{
				m_State = Player::ActionState::Running;
				m_Direction = MoveableEntity::Direction::Right;

				setToAnimation("REAPER_RUNNING_RIGHT", "RUNNING_RIGHT");
			}
			else
			{
				addVelocity(Vec2(100.f, 0.f));
				m_Animation->update(dt);
			}
			break;
		}

		case Action::A_RunLeft:
		{
			if (m_Direction == MoveableEntity::Direction::Right || m_State != Player::ActionState::Running)
			{
				m_State = Player::ActionState::Running;
				m_Direction = MoveableEntity::Direction::Right;

				setToAnimation("REAPER_RUNNING_LEFT", "RUNNING_LEFT");
			}
			else
			{
				addVelocity(Vec2(-100.f, 0.f));
				m_Animation->update(dt);
			}
			break;
		}

		case Action::A_None:
		default:
		{
			if (m_Direction == MoveableEntity::Direction::Right && m_State != Player::ActionState::Idle)
			{
				m_State = Player::ActionState::Idle;
				setToAnimation("REAPER_IDLE_RIGHT", "IDLE_RIGHT");
			}
			else if (m_Direction == MoveableEntity::Direction::Left && m_State != Player::ActionState::Idle)
			{
				m_State = Player::ActionState::Idle;
				setToAnimation("REAPER_IDLE_LEFT", "IDLE_LEFT");
			}
			break;
		}
		}
		

		// Run
		//if (KEY_PRESSED(D) && KEY_PRESSED(LShift) && MOUSE_PRESSED(Left))
		//{
		//	if (m_State != Player::ActionState::RunningSlashing)
		//	{
		//		m_State = Player::ActionState::RunningSlashing;

		//		setToAnimation("REAPER_RUNNING_SLASHING_RIGHT", "RUNNING_SLASHING_RIGHT");
		//	}
		//	else
		//	{
		//		if (m_Animation->isAnimationDone())
		//		{
		//			m_State = Player::ActionState::Running;
		//			setToAnimation("REAPER_RUNNING_RIGHT", "RUNNING_RIGHT");
		//		}
		//		else
		//		{
		//			auto deltaPos = (m_Vel * RUNNING_SPEEDUP) * dt;
		//			setPosition(m_Pos + deltaPos);
		//			/*m_Pos += (m_Vel * RUNNING_SPEEDUP) * dt;
		//			m_Sprite.setPosition(m_Pos.x, m_Pos.y);*/
		//			m_Animation->update(dt);
		//		}
		//	}
		//}
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		//{
		//	if (m_Direction == MoveableEntity::Direction::Left || m_State != Player::ActionState::Running)
		//	{
		//		m_State = Player::ActionState::Running;
		//		m_Direction = MoveableEntity::Direction::Right;

		//		setToAnimation("REAPER_RUNNING_RIGHT", "RUNNING_RIGHT");
		//	}
		//	else
		//	{
		//		/*m_Pos += (m_Vel * RUNNING_SPEEDUP) * dt;
		//		m_Sprite.setPosition(m_Pos.x, m_Pos.y);*/
		//		auto deltaPos = (m_Vel * RUNNING_SPEEDUP) * dt;
		//		setPosition(m_Pos + deltaPos);
		//		m_Animation->update(dt);
		//		m_deviceContext->m_resourceManager->playSound("RUNNING_AUDIO");
		//	}
		//}

		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		//{
		//	if (m_Direction == MoveableEntity::Direction::Right || m_State != Player::ActionState::Running)
		//	{
		//		m_State = Player::ActionState::Running;
		//		m_Direction = MoveableEntity::Direction::Left;

		//		setToAnimation("REAPER_RUNNING_LEFT", "RUNNING_LEFT");
		//	}
		//	else
		//	{
		//		//m_Pos -= (m_Vel * RUNNING_SPEEDUP) * dt;
		//		//m_Sprite.setPosition(m_Pos.x, m_Pos.y);

		//		auto deltaPos = (m_Vel * RUNNING_SPEEDUP) * dt;
		//		setPosition(m_Pos - deltaPos);
		//		m_Animation->update(dt);
		//	}
		//}

		//// Walk
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		//{

		//	 if (m_Direction == MoveableEntity::Direction::Left || m_State != Player::ActionState::Moving)
		//	{
		//		m_State = Player::ActionState::Moving;
		//		m_Direction = MoveableEntity::Direction::Right;

		//		setToAnimation("REAPER_WALKING_RIGHT", "WALKING_RIGHT");
		//	}
		//	else if (m_Direction == MoveableEntity::Direction::Right)
		//	{
		//		auto deltaPos = m_Vel * dt;
		//		setPosition(m_Pos + deltaPos);
		//		//m_Sprite.setPosition(m_Pos.x, m_Pos.y);
		//		m_Animation->update(dt);
		//	}
		//}
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		//{
		//	if (m_Direction == MoveableEntity::Direction::Right || m_State != Player::ActionState::Moving)
		//	{
		//		m_State = Player::ActionState::Moving;
		//		m_Direction = MoveableEntity::Direction::Left;

		//		setToAnimation("REAPER_WALKING_LEFT", "WALKING_LEFT");
		//	}
		//	else if (m_Direction == MoveableEntity::Direction::Left)
		//	{
		//		//m_Pos -= (m_Vel * dt);
		//		//m_Sprite.setPosition(m_Pos.x, m_Pos.y);
		//		auto deltaPos = m_Vel * dt;
		//		setPosition(m_Pos - deltaPos);
		//		m_Animation->update(dt);
		//	}
		//	
		//}

		//else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_State != Player::ActionState::Slashing && m_Direction == MoveableEntity::Direction::Right)
		//{
		//	m_State = Player::ActionState::Slashing;

		//	setToAnimation("REAPER_SLASHING_RIGHT", "SLASHING_RIGHT");
		//}

		//else if (m_State == Player::ActionState::Slashing)
		//{
		//	if (m_Animation->isAnimationDone())
		//	{
		//		m_State = Player::ActionState::Idle;

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
		//	if (m_State != Player::ActionState::Idle)
		//	{
		//		m_State = Player::ActionState::Idle;
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
		//	if (m_State != Player::ActionState::Idle)
		//	{
		//		m_State = Player::ActionState::Idle;
		//		
		//		setToAnimation("REAPER_IDLE_LEFT", "IDLE_LEFT");
		//	}
		//	else
		//	{
		//		m_Animation->update(dt);
		//	}
		//}
	}

	void Player::render() const
	{
		MoveableEntity::render();
	}

	sf::Sprite* Player::getSprite()
	{
		return MoveableEntity::getSprite();
	}

	void Player::setPosition(const Vec2& pos)
	{
		MoveableEntity::setPosition(pos);
	}

	void Player::setVelocity(const Vec2& vel)
	{
		MoveableEntity::setVelocity(vel);
	}

	void Player::setAcceleration(const Vec2& vel)
	{
		MoveableEntity::setAcceleration(vel);
	}

	void Player::setDirection(Direction dir)
	{
		MoveableEntity::setDirection(dir);
	}

	MoveableEntity::Direction Player::getDirection() const
	{
		return MoveableEntity::getDirection();
	}

	void Player::createAnimationList(const std::string& fileName)
	{
		MoveableEntity::createAnimationList(fileName);
	}

	void Player::setAnimation(const std::string& name)
	{
		MoveableEntity::setAnimation(name);
	}

	void Player::setBoundingBoxDimensions(unsigned int w, unsigned int h)
	{
		MoveableEntity::setBoundingBoxDimensions(w, h);
	}

	float Player::getPositionX() const
	{
		return m_Pos.x;
	}

	float Player::getPositionY() const
	{
		return m_Pos.y;
	}

	void Player::addVelocity(const Vec2& vel)
	{
		m_Vel += vel;
	}



	void Player::setToAnimation(const std::string& textureName, const std::string& animationName)
	{
		m_Sprite.setTexture(m_deviceContext->m_resourceManager->getTexture(textureName));
		m_Sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
		setAnimation(animationName);
		m_Animation->reset();
	}

	

}

