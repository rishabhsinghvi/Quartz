#include "Animation.h"

namespace Quartz
{
	void Animation::addFrame(const sf::IntRect & frame)
	{
		m_Frames.push_back(frame);
	}

	void Animation::addFrame(sf::IntRect && frame)
	{
		m_Frames.push_back(std::move(frame));
	}

	void Animation::addFrame(int x, int y, int w, int h)
	{
		m_Frames.emplace_back(x, y, w, h);
	}






}