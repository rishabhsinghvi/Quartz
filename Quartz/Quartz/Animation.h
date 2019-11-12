#ifndef QUARTZ_ANIMATION_H
#define QUARTZ_ANIMATION_H

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"

#include<memory>
#include<vector>

namespace Quartz
{
	class Animation
	{
	private:
		std::vector<sf::IntRect> m_Frames;
	
	public:

		void addFrame(const sf::IntRect& frame);

		void addFrame(sf::IntRect&& frame);

		void addFrame(int x, int y, int w, int h);

	};

	
}



#endif