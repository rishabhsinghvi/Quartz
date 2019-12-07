#include "Animation.h"

namespace Quartz
{
	Animation::Animation(sf::Texture* tex): m_Texture(tex)
	{
	}

	void Animation::addFrame(const sf::IntRect& intRect)
	{
		m_animFrames.push_back(intRect);
	}

	void Animation::setTexture(sf::Texture* tex)
	{
		m_Texture = tex;
	}

	sf::Texture* Animation::getTexture() const
	{
		return m_Texture;
	}

	const sf::IntRect& Animation::getFrame(int t) const
	{
		return m_animFrames.at(t);
	}

	int Animation::getNumFrames() const
	{
		return m_animFrames.size();
	}




}