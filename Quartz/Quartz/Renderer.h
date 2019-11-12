#ifndef QUARTZ_RENDERER_H
#define QUARTZ_RENDERER_H

#include<memory>

#include "ResourceManager.h"

#include "SFML/Graphics.hpp"

namespace Quartz
{
	class Renderer
	{
	private:
		sf::RenderWindow* m_renderWindow = nullptr;

	public:
		void init(sf::RenderWindow* window);
	};
}

#endif