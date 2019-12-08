#ifndef QUARTZ_PLAYER_ENTITY_H
#define QUARTZ_PLAYER_ENTITY_H

#include "MoveableEntity.h"

namespace Quartz
{
	class PlayerEntity : public MoveableEntity
	{
	public:
		PlayerEntity(DeviceContext* dc);
	};
}

#endif