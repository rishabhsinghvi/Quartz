#include "TileMap.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Logger/Logger.h"

#include "JSON/json.hpp"

#include<fstream>

namespace Quartz
{

	extern const std::string TILEMAP_DIRECTORY;

	TileMap::TileMap(const std::string& textureName, unsigned int tileSizeX, unsigned int tileSizeY, unsigned int tileMapWidth, unsigned int tileMapHeight, DeviceContext* dc):
		m_textureName(textureName), m_tileSizeX(tileSizeX), m_tileSizeY(tileSizeY), m_tileMapWidth(tileMapWidth), m_tileMapHeight(tileMapHeight), m_deviceContext(dc)
	{
	}

	void TileMap::createTileMap(const std::string& fileName)
	{
		using json = nlohmann::json;


		std::ifstream file(TILEMAP_DIRECTORY + fileName);

		if (!file)
		{
			LOG_FAILURE("Unable to open tile map file: {0}", fileName); 
		}

		json root;

		file >> root;

		const auto& layers = root["layers"];

		auto texturePtr = m_deviceContext->m_resourceManager->getTexturePointer(m_textureName);

		for (const auto& layer : layers)
		{
			const auto& layerData = layer["data"];

			sf::VertexArray vertices;
			vertices.setPrimitiveType(sf::Quads);
			vertices.resize(m_tileMapWidth * m_tileMapHeight * 4);

			
			for (auto i = 0; i < m_tileMapWidth; i++)
			{
				for (auto j = 0; j < m_tileMapHeight; j++)
				{
					int tileNumber = layerData[i + j * m_tileMapWidth] - 1;

					int tu = tileNumber % (texturePtr->getSize().x / m_tileSizeX);
					int tv = tileNumber / ((texturePtr->getSize().y / m_tileSizeY) - 1);

					auto quad = &vertices[(i + j * m_tileMapWidth) * 4];

					// define its 4 corners
					quad[0].position = sf::Vector2f(i * m_tileSizeX, j * m_tileSizeY);
					quad[1].position = sf::Vector2f((i + 1) * m_tileSizeX, j * m_tileSizeY);
					quad[2].position = sf::Vector2f((i + 1) * m_tileSizeX, (j + 1) * m_tileSizeY);
					quad[3].position = sf::Vector2f(i * m_tileSizeX, (j + 1) * m_tileSizeY);

					// define its 4 texture coordinates
					quad[0].texCoords = sf::Vector2f(tu * m_tileSizeX, tv * m_tileSizeY);
					quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSizeX, tv * m_tileSizeY);
					quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSizeX, (tv + 1) * m_tileSizeY);
					quad[3].texCoords = sf::Vector2f(tu * m_tileSizeX, (tv + 1) * m_tileSizeY);



				}
			}

			m_Vertices.push_back(std::move(vertices));
		}

		m_tileMapCreated = true;
	}

	void TileMap::render() const
	{
		m_deviceContext->m_Window->getRenderWindow()->draw(*this);
	}



	void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (!m_tileMapCreated)
		{
			LOG_WARN("The tile map must be created first!");
			return;
		}

		states.transform *= getTransform();

		states.texture = m_deviceContext->m_resourceManager->getTexturePointer(m_textureName);

		for (const auto& x : m_Vertices)
		{
			target.draw(x, states);
		}
	}


}