#pragma once

#include "RAPIER/Core/Ref.h"
#include "RAPIER/Scene/Scene.h"
#include "RAPIER/Core/Events/Event.h"

namespace RAPIER
{
	class EditorPanel : public RefCounted
	{
	public:
		virtual void OnImGuiRender(bool& isOpen) = 0;
		virtual void OnEvent(Event& e) {}
		virtual void SetsceneContext(const Ref<Scene>& context) {}
	};
}	// END namespace RAPIER
