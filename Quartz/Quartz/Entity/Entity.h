#ifndef QUARTZ_ENTITY_H
#define QUARTZ_ENTITY_H

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Math/Vec2.h"

#include<string>

namespace Quartz
{
	class Entity
	{
	public:
		enum class EntityType
		{
			Default, Moveable 
		};
	
	public:

		virtual void setSprite(const sf::Sprite& sprite) = 0;

		virtual void setPosition(const Vec2& pos) = 0;

		virtual void setVelocity(const Vec2& vec) = 0;

		virtual void update(float dt) = 0;

		virtual void render() const = 0;

		virtual sf::Sprite* getSprite() = 0;

	};
}

#endif