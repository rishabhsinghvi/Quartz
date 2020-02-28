#include "Entity.h"
#include "Window.h"


#include<fstream>

namespace Quartz
{
	extern const std::string ANIMATION_DIRECTORY;
}

Quartz::Entity::Entity(DeviceContext* dc) :
	m_deviceContext(dc)
{

}

void Quartz::Entity::setSprite(const sf::Sprite& sprite)
{
	m_Sprite = sprite; 

#ifdef DRAW_DEBUG_SHAPE
	m_debugShape.setSize(sf::Vector2f(m_Sprite.getScale().x * 100, m_Sprite.getScale().y * 100));
#endif
}

void Quartz::Entity::setPosition(const Vec2& pos)
{
	m_Pos = pos;
	m_Sprite.setPosition(m_Pos.x, m_Pos.y);

#ifdef DRAW_DEBUG_SHAPE
	m_debugShape.setPosition(sf::Vector2f(m_Pos.x, m_Pos.y));
	m_debugShape.setFillColor(sf::Color::Magenta);
	m_debugShape.setOutlineColor(sf::Color::Red);
#endif
}

void Quartz::Entity::setAcceleration(const Vec2& vel)
{
	// NOTHING
}

void Quartz::Entity::createAnimationList(const std::string& fileName)
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

void Quartz::Entity::setAnimation(const std::string& name)
{
	auto find = m_AnimationList.find(name);

	if (find == m_AnimationList.end())
	{
		LOG_ERROR("Unable to open Animation file: {0}", name);
	}

	m_Animation = find->second.get();
}

void Quartz::Entity::setSpriteDimensions(unsigned int w, unsigned int h)
{
	m_SpriteWidth = w;
	m_SpriteHeight = h;

#ifdef DRAW_DEBUG_SHAPE
	m_debugShape.setSize(sf::Vector2f(m_SpriteWidth, m_SpriteHeight));
#endif
}

void Quartz::Entity::addAcceleration(const Vec2& force)
{
	// NOTHING
}

void Quartz::Entity::update(float dt)
{
	m_Animation->update(dt);
}

void Quartz::Entity::render() const
{

	m_deviceContext->m_Window->getRenderWindow()->draw(m_Sprite);

#ifdef DRAW_DEBUG_SHAPE
	m_deviceContext->m_Window->getRenderWindow()->draw(m_debugShape);
#endif
}

sf::Sprite* Quartz::Entity::getSprite()
{
	return &m_Sprite;
}

void Quartz::Entity::setVelocity(const Vec2& vec)
{
	// NOTHING
}

const Quartz::Vec2& Quartz::Entity::getPosition() const
{
	return m_Pos;
}




