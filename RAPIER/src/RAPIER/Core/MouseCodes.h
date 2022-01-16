#pragma once

namespace RAPIER
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0					= 0,
		Button1					= 1,
		Button2					= 2,
		Button3					= 3,
		Button4					= 4,
		Button5					= 5,
		Button6					= 6,
		Button7					= 7,

		ButtonLast				= Button7,
		ButtonLeft				= Button0,
		ButtonRight				= Button1,
		ButtonMiddle			= Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}	//	END namespace RAPIER

#define RP_MOUSE_BUTTON_0      ::RAPIER::Mouse::Button0
#define RP_MOUSE_BUTTON_1      ::RAPIER::Mouse::Button1
#define RP_MOUSE_BUTTON_2      ::RAPIER::Mouse::Button2
#define RP_MOUSE_BUTTON_3      ::RAPIER::Mouse::Button3
#define RP_MOUSE_BUTTON_4      ::RAPIER::Mouse::Button4
#define RP_MOUSE_BUTTON_5      ::RAPIER::Mouse::Button5
#define RP_MOUSE_BUTTON_6      ::RAPIER::Mouse::Button6
#define RP_MOUSE_BUTTON_7      ::RAPIER::Mouse::Button7
#define RP_MOUSE_BUTTON_LAST   ::RAPIER::Mouse::ButtonLast
#define RP_MOUSE_BUTTON_LEFT   ::RAPIER::Mouse::ButtonLeft
#define RP_MOUSE_BUTTON_RIGHT  ::RAPIER::Mouse::ButtonRight
#define RP_MOUSE_BUTTON_MIDDLE ::RAPIER::Mouse::ButtonMiddle