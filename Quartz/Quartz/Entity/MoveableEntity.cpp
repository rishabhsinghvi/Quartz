#include "MoveableEntity.h"
#include "Window.h"
#include "ResourceManager.h"
#include "Logger/Logger.h"

#include "SFML/Graphics.hpp"

#include "JSON/json.hpp"

#include<fstream>
#include<iostream>

namespace Quartz
{
	extern const std::string ANIMATION_DIRECTORY;

	MoveableEntity::MoveableEntity(DeviceContext* w): Entity(w)
	{	
	}

	

	Vec2 MoveableEntity::getVelocity() const
	{
		return m_Vel;
	}

	/*void MoveableEntity::setPosition(const Vec2& pos)
	{
		Entity::setPosition(pos);
	}*/

	void MoveableEntity::setVelocity(const Vec2& vel)
	{
		m_Vel = vel;
	}

	void MoveableEntity::setAcceleration(const Vec2& acc)
	{
		m_Acc = acc;
	}

	MoveableEntity::Direction MoveableEntity::getDirection() const
	{
		return m_Direction;
	}

	

	void MoveableEntity::setVelocityX(float x)
	{
		m_Vel.x = x;
	}

	void MoveableEntity::setVelocityY(float y)
	{
		m_Vel.y = y;
	}



	void MoveableEntity::addAcceleration(const Vec2& force)
	{
		m_Acc += force;
	}


	Entity::EntityType MoveableEntity::getEntityType() const
	{
		return m_entityType;
	}

	void MoveableEntity::setDirection(MoveableEntity::Direction dir)
	{
		m_Direction = dir;
	}

}