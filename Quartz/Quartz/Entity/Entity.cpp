#include "Entity.h"
#include "Window.h"


#include<fstream>

namespace Quartz
{
	extern const std::string ANIMATION_DIRECTORY;
	extern const unsigned int WINDOW_WIDTH;
	extern const unsigned int WINDOW_HEIGHT;
}

Quartz::Entity::Entity(DeviceContext* dc) :
	m_deviceContext(dc)
{

}

void Quartz::Entity::setSprite(const sf::Sprite& sprite)
{
	m_Sprite = sprite; 
}

void Quartz::Entity::setPosition(const Vec2& pos)
{
	auto deltaPos = pos - m_Pos;
	m_Pos = pos;
	m_Sprite.setPosition(m_Pos.x, m_Pos.y);

	m_BoundingBoxData.x += deltaPos.x;
	m_BoundingBoxData.y += deltaPos.y;

	m_BoundingBoxData.m_BoundingBox.left = m_BoundingBoxData.x;
	m_BoundingBoxData.m_BoundingBox.top = m_BoundingBoxData.y;

#ifdef DRAW_DEBUG_SHAPE
	m_debugShape.setPosition(sf::Vector2f(m_BoundingBoxData.m_BoundingBox.left, m_BoundingBoxData.m_BoundingBox.top));
	m_debugShape.setFillColor(sf::Color::Transparent);
	m_debugShape.setOutlineThickness(3.0f);
	m_debugShape.setOutlineColor(sf::Color::Red);
#endif
}

void Quartz::Entity::setAcceleration(const Vec2& vel)
{
	// NOTHING; Only Moveable Entities can move
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

void Quartz::Entity::setBoundingBoxDimensions(float w, float h)
{
	m_BoundingBoxData.width = w;
	m_BoundingBoxData.height = h;

#ifdef DRAW_DEBUG_SHAPE
	m_debugShape.setSize(sf::Vector2f(w, h));
#endif
}

void Quartz::Entity::setBoundingBoxPositions(float x, float y)
{
	m_BoundingBoxData.x = x;
	m_BoundingBoxData.y = y;

#ifdef DRAW_DEBUG_SHAPE
	m_debugShape.setPosition(sf::Vector2f(x, y));
#endif
}

void Quartz::Entity::setBoundingBox(float x, float y, float w, float h)
{
	m_BoundingBoxData.x = x * WINDOW_WIDTH;
	m_BoundingBoxData.y = y * WINDOW_HEIGHT;
	m_BoundingBoxData.width = w;
	m_BoundingBoxData.height = h;

	m_BoundingBoxData.m_BoundingBox = sf::FloatRect(m_BoundingBoxData.x , m_BoundingBoxData.y, m_BoundingBoxData.width, m_BoundingBoxData.height);
	
#ifdef DRAW_DEBUG_SHAPE
	m_debugShape.setPosition(m_BoundingBoxData.x, m_BoundingBoxData.y);
	m_debugShape.setSize(sf::Vector2f(w,h));
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

const Quartz::Entity::BoundingBoxData& Quartz::Entity::getBoundingBoxData() const
{
	return m_BoundingBoxData;
}

void Quartz::Entity::setVelocity(const Vec2& vec)
{
	// NOTHING; only Moveable Entities can set their velocity
}

const Quartz::Vec2& Quartz::Entity::getPosition() const
{
	return m_Pos;
}




