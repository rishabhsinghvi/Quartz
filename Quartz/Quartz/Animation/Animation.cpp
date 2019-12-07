#include "Animation.h"

namespace Quartz
{
	Animation::Animation(sf::Sprite* sprite): m_Sprite(sprite)
	{
	}

	void Animation::setSprite(sf::Sprite* sprite)
	{
		m_Sprite = sprite;
	}

	void Animation::addFrame(const Frame& frame)
	{
		m_totalAnimationTime += frame.m_Duration;
		m_Frames.push_back(frame);
	}

	void Animation::addFrame(Frame&& frame)
	{
		m_totalAnimationTime += frame.m_Duration;
		m_Frames.push_back(std::move(frame));
	}

	void Animation::update(float dt)
	{
		m_currentTime += dt;
	
		float p = 0.0f;

		for (auto i = 0; i <= m_currentFrameIndex; i++)
		{
			p += m_Frames[i].m_Duration;
		}

		

		if (m_currentTime >= p)
		{
			if (m_currentFrameIndex == m_Frames.size() - 1)
			{
				reset();
			}
			else
			{
				m_currentFrameIndex += 1;
			}
		}

		m_Sprite->setTextureRect(m_Frames[m_currentFrameIndex].m_Rect);
		
	}



	float Animation::getLength() const
	{
		return m_totalAnimationTime;
	}

	void Animation::reset()
	{
		m_currentFrameIndex = 0;
		m_currentTime = 0.0f;
	}




}