#ifndef QUARTZ_ANIMATION_H
#define QUARTZ_ANIMATION_H

#include "SFML/Graphics.hpp"

#include <vector>

namespace Quartz
{
	struct Frame
	{
		sf::IntRect m_Rect;
		float m_Duration;
	};

	class Animation
	{
	private:
		std::vector<Frame> m_Frames;
		float m_totalAnimationTime = 0.0f;
		float m_currentTime = 0.0f;
		float m_currentFrameIndex = 0; 
		sf::Sprite* m_Sprite = nullptr;

	public:

		Animation() = default;

		Animation(sf::Sprite* sprite);

		void setSprite(sf::Sprite* sprite);

		void addFrame(const Frame& frame);
		void addFrame(Frame&& frame);

		void update(float dt);

		float getLength() const;

		void reset();

	};


}


#endif