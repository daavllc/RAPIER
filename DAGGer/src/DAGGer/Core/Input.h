/////////////////////////////////////////////////////////////////
//  Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the abstracted definitions for inputs
////////////////////////////////
#pragma once

#include "DAGGer/Core/Base.h"
#include "DAGGer/Core/KeyCodes.h"
#include "DAGGer/Core/MouseCodes.h"

namespace DAGGer
{
	class Input 
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}	//	END namespace DAGGer
