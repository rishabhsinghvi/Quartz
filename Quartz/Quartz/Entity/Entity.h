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

		struct BoundingBoxData
		{
			sf::Rect<float> m_BoundingBox;
			float width;
			float height;
			float x; 
			float y; 
		};
	protected:
		DeviceContext* m_deviceContext = nullptr;
		Animation* m_Animation = nullptr;
		sf::Sprite m_Sprite;
		Vec2 m_Pos;

		std::unordered_map<std::string, std::unique_ptr<Animation>> m_AnimationList;		

		BoundingBoxData m_BoundingBoxData;

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

		virtual void setBoundingBoxDimensions(float w, float h);

		virtual void setBoundingBoxPositions(float x, float y);

		virtual void setBoundingBox(float x, float y, float w, float h);

		virtual void addAcceleration(const Vec2& force);

		virtual void update(float dt);

		virtual void render() const;

		virtual sf::Sprite* getSprite();

		const BoundingBoxData& getBoundingBoxData() const;


	};
}

#endif