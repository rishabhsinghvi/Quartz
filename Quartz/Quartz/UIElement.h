#ifndef QUARTZ_UI_ELEMENT_H
#define QUARTZ_UI_ELEMENT_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"

namespace Quartz
{
	class UIElement : public sf::Drawable, public sf::Transformable
	{
	public:
		virtual bool contains(float x, float y) const = 0;

		virtual void onHover(float x, float y) = 0;
	private:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;


	};
}

#endif