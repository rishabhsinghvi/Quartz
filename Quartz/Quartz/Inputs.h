#ifndef QUARTZ_KEYCODES_H
#define QUARTZ_KEYCODES_H

namespace Quartz
{
	enum class Keycode
	{
			K_None = 0,
			K_A,
			K_D,
			K_ShiftA,
			K_ShiftD,
			K_Space,
			M_Left,
			K_AMouse1,
			K_DMouse1
	};


	enum class Action
	{
		A_None = 0,
		A_Jump,
		A_WalkRight,
		A_WalkLeft,
		A_RunRight,
		A_RunLeft,
		A_Slash
	};
}

#endif