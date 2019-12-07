#include "PlayerEntity.h"
#include "Window.h"

#include "SFML/Graphics.hpp"

namespace Quartz
{
	PlayerEntity::PlayerEntity(DeviceContext* w): m_deviceContext(w), m_currentAnimation(nullptr)
	{
		
	}

	void PlayerEntity::setSprite(const AnimatedSprite& sprite)
	{
		m_Sprite = sprite;
	}

	void PlayerEntity::pushAnimation(const std::string& name, std::unique_ptr<Animation>&& anim)
	{
		m_AnimationList[name] = std::move(anim);
	}

	void PlayerEntity::startAnimation()
	{
		m_Sprite.startAnimation();
	}

	void PlayerEntity::setAnimation(const std::string& anim)
	{
		auto find = m_AnimationList.find(anim);

		if (find == m_AnimationList.end())
		{
			return;
		}

		m_currentAnimation = find->second.get();
		m_Sprite.setAnimation(m_currentAnimation);
		m_Sprite.resetAnimation();
	}



	void PlayerEntity::update(float dt)
	{
		m_Sprite.update(dt);
	}

	void PlayerEntity::render() const
	{
		m_deviceContext->m_Window->getRenderWindow()->draw(m_Sprite);
	}
}