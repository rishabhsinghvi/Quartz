#include "AnimatedSprite.h"


namespace Quartz
{
	void AnimatedSprite::setAnimation(Animation* anim)
	{
		m_Animation = anim;
	}

	void AnimatedSprite::setFrameTime(float time)
	{
		m_FrameTime = time;
	}

	void AnimatedSprite::setLooping(bool val)
	{
		m_Looping = true;
	}

	void AnimatedSprite::startAnimation()
	{
		m_Playing = true;
	}

	void AnimatedSprite::pauseAnimation()
	{
		m_Playing = false;
	}

	void AnimatedSprite::stopAnimation()
	{
		m_Playing = false;
		
	}

	void AnimatedSprite::resetAnimation()
	{
		m_currentTime = 0.0f;
	}

	void AnimatedSprite::update(float dt)
	{
		if (!m_Playing)
			return;

		m_currentTime += dt;

		if (m_currentTime >= m_FrameTime)
		{
			// ?
			m_currentTime = 0.0f;

			if (m_currentFrame + 1 < m_Animation->getNumFrames())
			{
				m_currentFrame += 1;
			}
			else
			{
				if (m_Looping)
				{
					m_currentFrame = 0;
				}
				else
				{
					stopAnimation();
				}
			}

			setFrame(m_currentFrame);

		}
	}

	void AnimatedSprite::setFrame(int frame)
	{
		auto rect = m_Animation->getFrame(frame);

		m_Vertices[0] = sf::Vector2f(0.0f, 0.0f);
		m_Vertices[1] = sf::Vector2f(0.0f, static_cast<float>(rect.height));
		m_Vertices[2] = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
		m_Vertices[3] = sf::Vector2f(static_cast<float>(rect.width), 0.0f);

		float left = static_cast<float>(rect.left) + 0.0001f;
		float right = left + static_cast<float>(rect.width);
		float top = static_cast<float>(rect.top);
		float bottom = top + static_cast<float>(rect.height);

		m_Vertices[0].texCoords = sf::Vector2f(left, top);
		m_Vertices[1].texCoords = sf::Vector2f(left, bottom);
		m_Vertices[2].texCoords = sf::Vector2f(right, bottom);
		m_Vertices[3].texCoords = sf::Vector2f(right, top);

	}

	sf::FloatRect AnimatedSprite::getLocalBounds() const
	{
		auto bounds = m_Animation->getFrame(m_currentFrame);

		float w = static_cast<float>(bounds.width);
		float h = static_cast<float>(bounds.height);

		return sf::FloatRect(0.0f, 0.0f, w, h);
	}

	sf::FloatRect AnimatedSprite::getGlobalBounds() const
	{
		return getTransform().transformRect(getLocalBounds());
	}

	bool AnimatedSprite::isPlaying() const
	{
		return false;
	}

	void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = m_Animation->getTexture();
		target.draw(m_Vertices.data(), 4, sf::Quads, states);
	}




}