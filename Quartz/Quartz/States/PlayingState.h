#ifndef QUARTZ_PLAYING_STATE_H
#define QUARTZ_PLAYING_STATE_H

#include "GameState.h"
#include "UI/UIElement.h"
#include "Entity/Entity.h"
#include "Entity/PlayerEntity.h"
#include "Animation/Animation.h"
#include "TileMap/TileMap.h"
#include "Physics/PhysicsEngine.h"

namespace Quartz
{
	class PlayingState : public GameState
	{
	private:
		DeviceContext* m_deviceContext = nullptr;
		sf::RenderWindow* m_renderWindow = nullptr;
		bool m_Initialized = false;
		std::vector<std::unique_ptr<UIElement>> m_UIEntities;
		std::vector<std::unique_ptr<Entity>> m_Entities;

		std::unique_ptr<PhysicsEngine> m_Physics;
		sf::View m_View;
		//

		TileMap m_tileMap;
		PlayerEntity* m_Player = nullptr;
		

	public:


		virtual void init(DeviceContext* dc) override;

		virtual void destroy() override;

		virtual void paused() override;

		virtual void resumed() override;

		virtual void render() override;

		virtual void update(float dt) override;

		virtual void handleInput(sf::Event& event) override;

		virtual bool isInitialized() const override;
	};
}

#endif