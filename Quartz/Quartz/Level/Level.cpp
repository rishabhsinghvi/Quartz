#include "Level/Level.h"
#include "Logger/Logger.h"
#include "ResourceManager.h"
#include "Window.h"

#include "JSON/json.hpp"

#include<fstream>

namespace Quartz
{
	extern const std::string LEVEL_DIRECTORY;
	extern const unsigned int WINDOW_WIDTH;
	extern const unsigned int WINDOW_HEIGHT;

	Level::Level(const std::string& level, DeviceContext* dc): m_Level(std::move(level)), m_deviceContext(dc)
	{
		buildLevel();
	}

	void Level::render()
	{
		m_deviceContext->m_Window->getRenderWindow()->draw(m_deviceContext->m_resourceManager->getSprite(m_backgroundSprite));
		m_tileMap->render();

		for (auto& x : m_Entities)
			x->render();

	}

	void Level::update(float dt)
	{
		for (auto& x : m_Entities)
		{
			x->update(dt);
		}
	}

	const std::vector<std::unique_ptr<Entity>>& Level::getEntityList() const
	{
		return m_Entities;
	}


	const std::unique_ptr<TileMap>& Level::getTileMap() const
	{
		return m_tileMap;
	}

	void Level::buildLevel()
	{
		using json = nlohmann::json;

		std::ifstream levelConfig(LEVEL_DIRECTORY + m_Level + ".json");

		if (!levelConfig)
		{
			LOG_FAILURE("Level Creator: Unable to open level config file: {0}" + m_Level);
		}

		json root;

		levelConfig >> root;

		m_backgroundSprite = root["BACKGROUND_SPRITE"];

		std::string tileMapConfig = root["TILEMAP_NAME"];
		std::string tileMapTexture = root["TILEMAP_TEXTURE_NAME"];
		unsigned int tileMapSizeX = root["TILEMAP_TILESIZE_X"];
		unsigned int tileMapSizeY = root["TILEMAP_TILESIZE_Y"];
		unsigned int tileMapWidth = root["TILEMAP_TILE_WIDTH"];
		unsigned int tileMapHeight = root["TILEMAP_TILE_HEIGHT"];

		m_tileMap = std::make_unique<TileMap>(tileMapTexture, tileMapSizeX, tileMapSizeY, tileMapWidth, tileMapHeight, m_deviceContext);
		m_tileMap->createTileMap(tileMapConfig);

		LOG_INFO("Level Creator: Successfully built TileMap from {0}:", tileMapConfig);

		const auto& entityInfo = root["ENTITIES_INFO"];

		for (const auto& entity : entityInfo)
		{
			std::string textureName = entity["ENTITY_SPRITE_TEXTURE"];
			unsigned int x = entity["ENTITY_SPRITE_RECT_X"];
			unsigned int y = entity["ENTITY_SPRITE_RECT_Y"];
			unsigned int w = entity["ENTITY_SPRITE_RECT_W"];
			unsigned int h = entity["ENTITY_SPRITE_RECT_H"];

			sf::Sprite sprite;
			sprite.setTexture(m_deviceContext->m_resourceManager->getTexture(textureName));
			sprite.setTextureRect(sf::IntRect(x, y, w, h));
			

			std::unique_ptr<MoveableEntity> ent;

			std::string entityType = entity["ENTITY_TYPE"];

			if (entityType == "PLAYER")
				ent = std::make_unique<Player>(m_deviceContext);
			else
				ent = std::make_unique<MoveableEntity>(m_deviceContext);

			float entityPosX = entity["ENTITY_INI_POS_X"];
			float entityPosY = entity["ENTITY_INI_POS_Y"];
			
			ent->setSprite(sprite);
			ent->setPosition(Vec2(entityPosX * static_cast<float>(WINDOW_WIDTH), entityPosY * static_cast<float>(WINDOW_HEIGHT)));

			//LOG_INFO("{0}, {1}", WINDOW_WIDTH, WINDOW_HEIGHT);
			//LOG_INFO("{0}, {1}", ent->getPosition().x, ent->getPosition().y);

			ent->setVelocity(Vec2(entity["ENTITY_INI_VEL_X"], entity["ENTITY_INI_VEL_Y"]));
			
			ent->createAnimationList(entity["ENTITY_ANIMATION_LIST"]);
			ent->setAnimation(entity["ENTITY_INI_ANIMATION"]);
			//ent->setBoundingBoxDimensions(entity["ENTITY_BOUNDING_BOX_WIDTH"], entity["ENTITY_BOUNDING_BOX_HEIGHT"]);
			ent->setBoundingBox(entity["ENTITY_BOUNDING_BOX_POS_X"], entity["ENTITY_BOUNDING_BOX_POS_Y"], entity["ENTITY_BOUNDING_BOX_WIDTH"], entity["ENTITY_BOUNDING_BOX_HEIGHT"]);

			if (entityType == "PLAYER")
				m_Player = static_cast<Player*>(ent.get());

			m_Entities.push_back(std::move(ent));

			// Physics register entity

		}

		m_levelBuilt = true;

		LOG_INFO("Level Creator: Level {0} successfully built.", m_Level);

	}

	
}