#pragma once

#include "RAPIER/Core/Base.h"
#include "RAPIER/Core/KeyCodes.h"
#include "RAPIER/Core/MouseCodes.h"

namespace RAPIER
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
}	//	END namespace RAPIER
