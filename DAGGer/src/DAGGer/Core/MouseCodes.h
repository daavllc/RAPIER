/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file contains DAGGer MouseCode definitions
////////////////////////////////
#pragma once

namespace DAGGer
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
}	//	END namespace DAGGer

#define Dr_MOUSE_BUTTON_0      ::DAGGer::Mouse::Button0
#define Dr_MOUSE_BUTTON_1      ::DAGGer::Mouse::Button1
#define Dr_MOUSE_BUTTON_2      ::DAGGer::Mouse::Button2
#define Dr_MOUSE_BUTTON_3      ::DAGGer::Mouse::Button3
#define Dr_MOUSE_BUTTON_4      ::DAGGer::Mouse::Button4
#define Dr_MOUSE_BUTTON_5      ::DAGGer::Mouse::Button5
#define Dr_MOUSE_BUTTON_6      ::DAGGer::Mouse::Button6
#define Dr_MOUSE_BUTTON_7      ::DAGGer::Mouse::Button7
#define Dr_MOUSE_BUTTON_LAST   ::DAGGer::Mouse::ButtonLast
#define Dr_MOUSE_BUTTON_LEFT   ::DAGGer::Mouse::ButtonLeft
#define Dr_MOUSE_BUTTON_RIGHT  ::DAGGer::Mouse::ButtonRight
#define Dr_MOUSE_BUTTON_MIDDLE ::DAGGer::Mouse::ButtonMiddle