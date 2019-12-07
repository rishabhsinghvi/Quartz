#include "PlayerEntity.h"
#include "Window.h"

#include "SFML/Graphics.hpp"

namespace Quartz
{
	PlayerEntity::PlayerEntity(DeviceContext* w): m_deviceContext(w)
	{	
	}

	void PlayerEntity::setSprite(const sf::Sprite& sprite)
	{
		m_Sprite = sprite;
	}

	



	void PlayerEntity::update(float dt)
	{
	}

	void PlayerEntity::render() const
	{
		m_deviceContext->m_Window->getRenderWindow()->draw(m_Sprite);
	}

	sf::Sprite* PlayerEntity::getSprite()
	{
		return &m_Sprite;
	}
}