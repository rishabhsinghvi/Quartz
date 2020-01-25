#ifndef QUARTZ_LEVEL_H
#define QUARTZ_LEVEL_H

#include "TileMap/TileMap.h"
#include "Entity/Entity.h"
#include "Entity/Player.h"
#include "Entity/MoveableEntity.h"
#include "DeviceContext.h"

#include<vector>
#include<memory>
#include<string>

namespace Quartz
{
	class Level
	{
	private:
		std::string m_Level;
		std::unique_ptr<TileMap> m_tileMap;
		std::vector<std::unique_ptr<MoveableEntity>> m_Entities;
		bool m_levelBuilt = false;
		std::string m_backgroundSprite;

		DeviceContext* m_deviceContext = nullptr;

		Player* m_Player = nullptr; // keep a pointer to player entity

	public:

		Level() = default;

		Level(const std::string& level, DeviceContext* dc);

		void render();

		void update(float dt);

		const std::vector<std::unique_ptr<MoveableEntity>>& getEntities() const;

		const std::unique_ptr<TileMap>& getTileMap() const;

	private:

		void buildLevel();

	};
}

#endif