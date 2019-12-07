#ifndef QUARTZ_PLAYER_ENTITY_H
#define QUARTZ_PLAYER_ENTITY_H

#include "Entity.h"
#include "Animation/Animation.h"
#include "Animation/AnimatedSprite.h"
#include "DeviceContext.h"

#include <unordered_map>
#include <string>
#include <memory>

namespace Quartz
{
	class PlayerEntity : public Entity
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<Animation>> m_AnimationList;
		AnimatedSprite m_Sprite;
		Animation* m_currentAnimation;
		DeviceContext* m_deviceContext;


	public:

		PlayerEntity(DeviceContext* w);

		void setSprite(const AnimatedSprite& sprite);

		void pushAnimation(const std::string&, std::unique_ptr<Animation>&& anim);

		void startAnimation();

		void setAnimation(const std::string& anim);

		virtual void update(float dt) override;

		virtual void render() const override;

		

	};
}

#endif