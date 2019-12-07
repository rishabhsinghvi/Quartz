#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

#include "Animation.h"

#include<array>

namespace Quartz
{
	class AnimatedSprite : public sf::Drawable, public sf::Transformable
	{
	private:
		Animation* m_Animation;
		float m_FrameTime;
		float m_currentTime;
		int m_currentFrame;
		bool m_Playing;
		bool m_Looping = false;
		std::array<sf::Vertex, 4> m_Vertices;

	public:

		AnimatedSprite() = default;

		void setAnimation(Animation* anim);

		void setFrameTime(float time);
		
		void setLooping(bool val);

		void startAnimation();

		void pauseAnimation();

		void stopAnimation();

		void resetAnimation();

		void update(float dt);

		void setFrame(int frame);

		sf::FloatRect getLocalBounds() const;

		sf::FloatRect getGlobalBounds() const;

		bool isPlaying() const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}

#endif