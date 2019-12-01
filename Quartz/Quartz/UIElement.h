#ifndef QUARTZ_UI_ELEMENT_H
#define QUARTZ_UI_ELEMENT_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"

namespace Quartz
{
	class UIElement : public sf::Drawable, public sf::Transformable
	{
	private:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;


	};
}

#endif