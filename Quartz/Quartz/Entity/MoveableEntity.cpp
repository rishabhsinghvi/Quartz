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

	MoveableEntity::MoveableEntity(DeviceContext* w): m_deviceContext(w)
	{	
	}

	void MoveableEntity::setSprite(const sf::Sprite& sprite)
	{
		m_Sprite = sprite;
	}

	void MoveableEntity::update(float dt)
	{
		
	}

	void MoveableEntity::render() const
	{
		m_deviceContext->m_Window->getRenderWindow()->draw(m_Sprite);
	}

	sf::Sprite* MoveableEntity::getSprite()
	{
		return &m_Sprite;
	}

	void MoveableEntity::setPosition(const Vec2& pos)
	{
		m_Pos = pos;
		m_Sprite.setPosition(m_Pos.x, m_Pos.y);
	}

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

	void MoveableEntity::createAnimationList(const std::string& fileName)
	{
		using json = nlohmann::json;
		
		std::ifstream file(ANIMATION_DIRECTORY + fileName);

		if (!file)
		{
			LOG_ERROR("Unable to open Animation file: {0}", fileName);
		}

		json root;

		file >> root;

		for (auto it = root.begin(); it != root.end(); it++)
		{
			auto anim = std::make_unique<Animation>();

			anim->setSprite(&m_Sprite);

			auto animName = it.key();
			
			auto val = it.value();

			anim->setLooping(val["LOOP"]);
			auto array = val["FRAMES"];
			for (json& f : array)
			{
				auto x = f["x"];
				auto y = f["y"];
				auto w = f["width"];
				auto h = f["height"];
				auto dur = f["duration"];

				anim->addFrame(x, y, w, h, dur);
			}

			m_AnimationList[animName] = std::move(anim);
		}

	}

	void MoveableEntity::setAnimation(const std::string& name)
	{
		auto find = m_AnimationList.find(name);

		if (find == m_AnimationList.end())
		{
			LOG_ERROR("Unable to open Animation file: {0}", name);
		}
		
		m_Animation = find->second.get();
	}

	void MoveableEntity::setSpriteDimensions(unsigned int w, unsigned int h)
	{
		m_SpriteWidth = w;
		m_SpriteHeight = h;
	}

	void MoveableEntity::setDirection(MoveableEntity::Direction dir)
	{
		m_Direction = dir;
	}







}