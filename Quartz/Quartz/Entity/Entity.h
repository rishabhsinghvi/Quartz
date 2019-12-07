#ifndef QUARTZ_ENTITY_H
#define QUARTZ_ENTITY_H

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include<string>

namespace Quartz
{
	class Entity
	{
	private:
	
	public:

		virtual void update(float dt) = 0;

		virtual void render() const = 0;

	};
}

#endif