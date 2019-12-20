#ifndef QUARTZ_TILE_H
#define QUARTZ_TILE_H

#include<string>

namespace Quartz
{
	struct Tile
	{
		unsigned int m_Id;
		unsigned int m_xOffset;
		unsigned int m_yOffset;
		
		bool m_Collidable;

		Tile() = default;

		Tile(unsigned int id, unsigned int x, unsigned int y, bool collidable = false) :
			m_Id(id), m_xOffset(x), m_yOffset(y), m_Collidable(collidable)
		{
			// EMPTY
		}
	
	};
}

#endif