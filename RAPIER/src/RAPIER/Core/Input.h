#pragma once

#include "RAPIER/Core/Base.h"
#include "RAPIER/Core/KeyCodes.h"
#include "RAPIER/Core/MouseCodes.h"

#include <map>

namespace RAPIER
{
	enum class CursorMode
	{
		Normal = 0,
		Hidden = 1,
		Locked = 2
	};

	struct Controller
	{
		int ID;
		std::string Name;
		std::map<int, bool> ButtonStates;
		std::map<int, float> AxisStates;
		std::map<int, uint8_t> HatStates;
	};

	class Input 
	{
	public:
		static void Update();

		//	Keyboard
		static bool IsKeyPressed(KeyCode key);
		//	Mouse
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
		//	CursorMode
		static void SetCursorMode(CursorMode mode);
		static CursorMode GetCursorMode();
		//	Controllers
		static bool IsControllerPresent(int id);
		static std::vector<int> GetConnectedControllerIDs();
		static const Controller* GetController(int id);
		static std::string_view GetControllerName(int id);
		static bool IsControllerButtonPressed(int controllerID, int button);
		static float GetControllerAxis(int controllerID, int axis);
		static uint8_t GetControllerHat(int controllerID, int hat);

		inline static const std::map<int, Controller>& GetControllers() { return s_Controllers; }
	private:
		inline static std::map<int, Controller> s_Controllers;
	};
}	//	END namespace RAPIER
