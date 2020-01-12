#ifndef QUARTZ_TILE_MAP_H
#define QUARTZ_TILE_MAP_H

#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/VertexArray.hpp"

#include "DeviceContext.h"

#include<vector>
#include<string>

namespace Quartz
{
	class TileMap : public sf::Drawable, public sf::Transformable
	{
	private:
		std::vector<sf::VertexArray> m_Vertices; // for multi-layer tile map
		std::vector<bool> m_Collidable;
		unsigned int m_tileSizeX, m_tileSizeY;
		unsigned int m_tileMapWidth, m_tileMapHeight;
		std::string m_textureName;
		bool m_tileMapCreated = false;
		DeviceContext* m_deviceContext = nullptr;
		

	public:

		TileMap() = default;

		TileMap(const std::string& textureName, unsigned int tileSizeX, unsigned int tileSizeY, unsigned int tileMapWidth, unsigned int tileMapHeight, DeviceContext* dc);

		void createTileMap(const std::string& fileName);

		void render() const;

		unsigned int getTileWidth() const;

		unsigned int getTileHeight() const;

		unsigned int getMapWidth() const;

		unsigned int getMapHeight() const;

		bool isCollidable(unsigned int x, unsigned int y) const;

	private:


		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}

#endif