#include "Animation.h"
#include "Logger/Logger.h"

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

	void Animation::addFrame(int x, int y, int w, int h, float dur)
	{
		sf::IntRect rect(x, y, w, h);
		addFrame({ std::move(rect), dur });
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
			if (m_currentFrameIndex == m_Frames.size() - 1 && m_Looping)
			{
				reset();
			}
			else if (m_currentFrameIndex == m_Frames.size() - 1 && !m_Looping)
			{
				m_Done = true;
				return;
			}
			else 
			{
				m_currentFrameIndex += 1;
			}
		}

		m_Done = false;
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

	void Animation::setLooping(bool val)
	{
		m_Looping = val;
	}

	bool Animation::isAnimationDone() const
	{
		return m_Done;
	}

	void Animation::setAnimationDone(bool val)
	{
		m_Done = val;
	}




}