#ifndef QUARTZ_ANIMATION_H
#define QUARTZ_ANIMATION_H

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"

#include<vector>

namespace Quartz
{
	class Animation
	{
	private:
		std::vector<sf::IntRect> m_animFrames;
		sf::Texture* m_Texture = nullptr;

	public:
		Animation() = default;
		Animation(sf::Texture* tex);

		void addFrame(const sf::IntRect& intRect);

		void setTexture(sf::Texture* tex);

		sf::Texture* getTexture() const;

		const sf::IntRect& getFrame(int t) const;

		int getNumFrames() const;
	};
}
#endif