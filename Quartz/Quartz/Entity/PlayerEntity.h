#ifndef QUARTZ_PLAYER_ENTITY_H
#define QUARTZ_PLAYER_ENTITY_H

#include "Entity.h"
#include "DeviceContext.h"
#include "Math/Vec2.h"

#include <unordered_map>
#include <string>
#include <memory>

namespace Quartz
{
	class PlayerEntity : public Entity
	{
	private:
		DeviceContext* m_deviceContext;
		sf::Sprite m_Sprite;
		Vec2 m_Pos;
		Vec2 m_Vel;
		Vec2 m_Acc;

	public:

		PlayerEntity(DeviceContext* w);

		void setSprite(const sf::Sprite& sprite); 

		virtual void update(float dt) override;

		virtual void render() const override;
		
		virtual sf::Sprite* getSprite() override;
		

	};
}

#endif