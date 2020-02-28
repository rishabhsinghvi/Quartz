#ifndef QUARTZ_ENTITY_H
#define QUARTZ_ENTITY_H

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Math/Vec2.h"
#include "Animation/Animation.h"
#include "Logger/Logger.h"
#include "DeviceContext.h"

#include "JSON/json.hpp"



#include<string>
#include<unordered_map>

namespace Quartz
{
	class Entity
	{
	public:
		enum class EntityType
		{
			Default, Moveable 
		};
	protected:
		DeviceContext* m_deviceContext = nullptr;
		Animation* m_Animation = nullptr;
		sf::Sprite m_Sprite;
		Vec2 m_Pos; 
		unsigned int m_SpriteWidth;
		unsigned int m_SpriteHeight;
		std::unordered_map<std::string, std::unique_ptr<Animation>> m_AnimationList;

#ifdef DRAW_DEBUG_SHAPE
		sf::RectangleShape m_debugShape;
#endif
	
	public:

		Entity(DeviceContext* dc);

		virtual void setSprite(const sf::Sprite& sprite);

		virtual void setPosition(const Vec2& pos);

		virtual void setVelocity(const Vec2& vec);

		virtual const Vec2& getPosition() const;

		virtual void setAcceleration(const Vec2& vel);

		virtual void createAnimationList(const std::string& fileName);

		virtual void setAnimation(const std::string& name);

		virtual void setSpriteDimensions(unsigned int w, unsigned int h);

		virtual void addAcceleration(const Vec2& force);

		virtual void update(float dt);

		virtual void render() const;

		virtual sf::Sprite* getSprite();

	};
}

#endif